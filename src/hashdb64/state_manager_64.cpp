#include "state_manager_64.hpp"
#include "zkassert.hpp"
#include "zklog.hpp"
#include "scalar.hpp"
#include "timer.hpp"
#include "persistence.hpp"
#include "definitions.hpp"
#include "tree_64.hpp"

Goldilocks frSM64;
PoseidonGoldilocks poseidonSM64;
StateManager64 stateManager64(frSM64, poseidonSM64);

zkresult StateManager64::setStateRoot(const string &batchUUID, uint64_t tx, const string &_stateRoot, const bool bIsOldStateRoot, const bool bVirtual, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize state root format
    string stateRoot = NormalizeToNFormat(_stateRoot, 64);
    stateRoot = stringToLower(stateRoot);

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager64::setStateRoot() invalid persistence batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager64::setStateRoot() batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState64>::iterator it;

    // Find batch state for this uuid, or create it if it does not exist
    it = state.find(batchUUID);
    if (it == state.end())
    {
        if (!bIsOldStateRoot)
        {
            zklog.error("StateManager64::setStateRoot() called with bIsOldStateRoot=false, but batchUUID=" + batchUUID + " does not previously exist");
            Unlock();
            return ZKR_STATE_MANAGER;
        }
        BatchState64 batchState;
        batchState.oldStateRoot.set(stateRoot, bVirtual);
        state[batchUUID] = batchState;
        it = state.find(batchUUID);
        zkassert(it != state.end());
    }
    BatchState64 &batchState = it->second;

    // Set the current state root
    batchState.currentStateRoot.set(stateRoot, bVirtual);

    // Create tx states, if needed
    if (tx >= batchState.txState.size())
    {
        // If this is the first state of a new tx, check that it is the old state root
        if (!bIsOldStateRoot)
        {
            zklog.error("StateManager64::setStateRoot() called with bIsOldStateRoot=false, but tx=" + to_string(tx) + " does not previously exist");
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Calculate the number of tx slots to create
        uint64_t txsToCreate = tx - batchState.txState.size() + 1;

        // Create TX state to insert
        TxState64 txState;

        // Insert TX state
        for (uint64_t i = 0; i < txsToCreate; i++)
        {
            batchState.txState.emplace_back(txState);
        }

        // Set current TX
        batchState.currentTx = tx;
    }

    // Get a reference to the tx state
    TxState64 &txState = batchState.txState[tx];

    // Get the current sub-state list size
    uint64_t currentSubStateSize = txState.persistence[persistence].subState.size();

    // In case it is an old state root, we need to create a new sub-state, and check that everything makes sense
    if (bIsOldStateRoot)
    {
        // If this is the first sub-state of the tx state, record the tx old state root
        if (currentSubStateSize == 0)
        {
            // Check current sub-state
            if (txState.persistence[persistence].currentSubState != 0)
            {
                zklog.error("StateManager64::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + "!=0 batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Record the old state root
            txState.persistence[persistence].oldStateRoot.set(stateRoot, bVirtual);
        }

        // If it is not the first sub-state, it must have been called with the previous new state root
        else
        {
            // Check current sub-state
            if (txState.persistence[persistence].currentSubState >= currentSubStateSize)
            {
                zklog.error("StateManager64::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + " > currentSubStateSize=" + to_string(currentSubStateSize) + " batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Check that new state root is empty
            if (txState.persistence[persistence].subState[currentSubStateSize - 1].newStateRoot.empty())
            {
                zklog.error("StateManager64::setStateRoot() oldStateRoot found previous newStateRoot empty");
                Unlock();
                return ZKR_STATE_MANAGER;
            }
        }

        // Create TX sub-state
        TxSubState64 txSubState;
        txSubState.oldStateRoot.set(stateRoot, bVirtual);
        txSubState.previousSubState = txState.persistence[persistence].currentSubState;

        // Copy the key-value data from the previous state, if it exists
        for (uint64_t i = 0; i < currentSubStateSize; i++)
        {
            if (txState.persistence[persistence].subState[i].newStateRoot.equals(stateRoot, bVirtual))
            {
                txSubState.dbWrite = txState.persistence[persistence].subState[i].dbWrite;
                break;
            }
        }

        // Insert it
        txState.persistence[persistence].subState.emplace_back(txSubState);

        // Record the current state
        txState.persistence[persistence].currentSubState = txState.persistence[persistence].subState.size() - 1;
    }

    // If it is a new state root, we need to complete the current sub-state
    else
    {
        if (txState.persistence[persistence].currentSubState >= currentSubStateSize)
        {
            zklog.error("StateManager64::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + " > currentSubStateSize=" + to_string(currentSubStateSize) + " batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Check that the new state root is empty
        if (!txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot.empty())
        {
            zklog.error("StateManager64::setStateRoot() found nesStateRoot busy");
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Record the new state root in the tx sub-state, and in the tx state
        txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot.set(stateRoot, bVirtual);
        txState.persistence[persistence].newStateRoot.set(stateRoot, bVirtual);
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("setStateRoot", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager64::write(const string &batchUUID, uint64_t tx, const string &_key, const mpz_class &value, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager64::write() batchUUID=" + batchUUID + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
#endif

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager64::write() wrong persistence batchUUID=" + batchUUID + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState64>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.error("StateManager64::write() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BatchState64 &batchState = it->second;

    // Check tx range
    if (tx >= batchState.txState.size())
    {
        zklog.error("StateManager64::write() got tx=" + to_string(tx) + " bigger than txState size=" + to_string(it->second.txState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Create TxState, if not existing
    /*if (tx == batchState.txState.size())
    {
        TxState64 aux;
        aux.persistence[persistence].oldStateRoot = it->second.currentStateRoot;
        it->second.txState.emplace_back(aux);
    }*/
    TxState64 &txState = batchState.txState[tx];

    // Create TxSubState, if not existing
    if (txState.persistence[persistence].subState.size() == 0)
    {
        TxSubState64 subState;
        subState.previousSubState = 0;
        subState.oldStateRoot = batchState.currentStateRoot;
        txState.persistence[persistence].subState.emplace_back(subState);
        txState.persistence[persistence].currentSubState = 0;
    }

    // Add to sub-state
    txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].dbWrite[key] = value;

    // Add to common write pool to speed up read
    batchState.dbWrite[key] = value;

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("write", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager64::read(const string &batchUUID, const string &_key, mpz_class &value, DatabaseMap *dbReadLog)
{
    struct timeval t;
    gettimeofday(&t, NULL);

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState64>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        // zklog.error("StateManager64::read() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_DB_KEY_NOT_FOUND;
    }
    BatchState64 &batchState = it->second;

    // Search in the common write list
    unordered_map<string, mpz_class>::iterator dbIt;
    dbIt = batchState.dbWrite.find(key);
    if (dbIt != batchState.dbWrite.end())
    {
        value = dbIt->second;

        // Add to the read log
        if (dbReadLog != NULL)
            dbReadLog->add(key, value.get_str(16), true, TimeDiff(t));

#ifdef LOG_STATE_MANAGER
        zklog.info("StateManager64::read() batchUUID=" + batchUUID + " key=" + key);
#endif

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        batchState.timeMetricStorage.add("read success", TimeDiff(t));
#endif
        Unlock();

        return ZKR_SUCCESS;
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("read not found", TimeDiff(t));
#endif

    Unlock();

    return ZKR_DB_KEY_NOT_FOUND;
}

bool IsInvalid(TxSubState64 &txSubState)
{
    return !txSubState.bValid;
}

zkresult StateManager64::semiFlush(const string &batchUUID, const string &_stateRoot, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize state root format
    string stateRoot = NormalizeToNFormat(_stateRoot, 64);
    stateRoot = stringToLower(stateRoot);
    bool bVirtual = isVirtualStateRoot(stateRoot);

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager64::semiFlush() invalid persistence batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager64::semiFlush() batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState64>::iterator it;

    // Find batch state for this uuid
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.warning("StateManager64::semiFlush() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        // timeMetricStorage.add("semiFlush UUID not found", TimeDiff(t));
        // timeMetricStorage.print("State Manager calls");
#endif
        Unlock();
        return ZKR_SUCCESS;
    }
    BatchState64 &batchState = it->second;

    // Check currentTx range
    if (batchState.currentTx >= batchState.txState.size())
    {
        zklog.error("StateManager64::semiFlush() found batchState.currentTx=" + to_string(batchState.currentTx) + " >= batchState.txState.size=" + to_string(batchState.txState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Get a reference to the tx state
    TxState64 &txState = batchState.txState[batchState.currentTx];
    TxPersistenceState64 &txPersistenceState = txState.persistence[persistence];

    if (txPersistenceState.newStateRoot.equals(stateRoot, bVirtual))
    {
        // This is the expected case
    }
    else if (txPersistenceState.oldStateRoot.equals(stateRoot, bVirtual))
    {
        if (config.stateManagerPurge)
        {
            // The TX ended up with the same state root as the beginning, so we can delete all data
            txPersistenceState.subState.clear();
            txPersistenceState.newStateRoot.set(stateRoot, bVirtual);
            txPersistenceState.currentSubState = 0;
        }
    }
    else
    {
        if (config.stateManagerPurge)
        {
            // Search for the point at which we reach this state, and delete the rest
            bool bFound = false;
            uint64_t i = 0;
            uint64_t subStateSize = txPersistenceState.subState.size();
            for (i = 0; i < subStateSize; i++)
            {
                if (!bFound && txPersistenceState.subState[i].oldStateRoot.equals(stateRoot, bVirtual))
                {
                    bFound = true;
                    break;
                }
            }
            if (bFound)
            {
                txPersistenceState.newStateRoot.set(stateRoot, bVirtual);
                txPersistenceState.currentSubState = (i == 0) ? 0 : i - 1;
                for (; i < subStateSize; i++)
                {
                    txPersistenceState.subState.pop_back();
                }
            }
        }
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("semi flush", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager64::flush(const string &batchUUID, const string &_newStateRoot, const Persistence persistence, Database64 &db, uint64_t &flushId, uint64_t &lastSentFlushId)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    TimerStart(STATE_MANAGER_FLUSH);

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager64::flush() batchUUID=" + batchUUID);
#endif

    // For every TX, track backwards from newStateRoot to oldStateRoot, marking sub-states as valid

    Lock();

    print(true);

    // Format the new state root
    string newStateRoot = NormalizeToNFormat(_newStateRoot, 64);
    bool bVirtual = isVirtualStateRoot(newStateRoot);

    zkresult zkr;

    // Find batch state for this uuid
    // If it does not exist, we call db.flush() directly
    unordered_map<string, BatchState64>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        // zklog.warning("StateManager64::flush() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");

        zkr = db.flush(flushId, lastSentFlushId);
        if (zkr != ZKR_SUCCESS)
        {
            zklog.error("StateManager64::flush() failed calling db.flush() result=" + zkresult2string(zkr));
        }

        TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        // timeMetricStorage.add("flush UUID not found", TimeDiff(t));
        // timeMetricStorage.print("State Manager calls");
#endif
        Unlock();
        return zkr;
    }
    BatchState64 &batchState = it->second;

    // For all txs, delete the ones that are not part of the final state root chain
    // Start searching from the last TX, and when a tx with the same new state root is found,
    // delete the rest (typically fruit of an out-of-counters condition)

    if (config.stateManagerPurgeTxs && (_newStateRoot.size() > 0) && (persistence == PERSISTENCE_DATABASE))
    {
        int64_t tx = -1;
        for (tx = batchState.txState.size() - 1; tx >= 0; tx--)
        {
            if (batchState.txState[tx].persistence[PERSISTENCE_DATABASE].newStateRoot.equals(newStateRoot, bVirtual))
            {
                break;
            }
        }
        if (tx < 0)
        {
            zklog.error("StateManager::flush() called with newStateRoot=" + newStateRoot + " but could not find it");
        }
        else
        {
            while ((int64_t)batchState.txState.size() > (tx + 1))
            {
                batchState.txState.pop_back();
            }
        }
    }

    // For all tx sub-states, purge the data to write:
    // - Delete all temporary data
    // - Mark sub-states that are part of the chain
    // - Delete the rest of sub-states

    // For all transactions
    for (uint64_t tx = 0; tx < batchState.txState.size(); tx++)
    {
        // Get a reference to the current transaction state
        TxState64 &txState = batchState.txState[tx];

        // For all persistences
        for (uint64_t persistence = 0; persistence < PERSISTENCE_SIZE; persistence++)
        {
            // If there's no data, there's nothing to do
            if (txState.persistence[persistence].subState.size() == 0)
            {
                continue;
            }

            // All data with temporary persistence can be deleted at the end of a batch
            if (persistence == PERSISTENCE_TEMPORARY)
            {
                txState.persistence[persistence].subState.clear();
                txState.persistence[persistence].currentSubState = 0;
                continue;
            }

            // Check that current sub-state newStateRoot matches the TX one,
            // i.e. that setNewStateRoot() was called before flush()
            if (txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot != txState.persistence[persistence].newStateRoot)
            {
                zklog.error("StateManager64::flush() found inconsistent new state roots: batchUUID=" + batchUUID +
                            " tx=" + to_string(tx) + " txState.newStateRoot=" + txState.persistence[persistence].newStateRoot.toString() +
                            " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                            " substate.newStateRoot=" + txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot.toString());

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("flush UUID inconsistent new state roots", TimeDiff(t));
                batchState.timeMetricStorage.print("State Manager calls");
#endif
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            uint64_t currentSubState = txState.persistence[persistence].currentSubState;

            // TODO: check that currentSubState == size(), or simply don't use it

            // Search for the chain of sub-states that end with this new state root
            // Mark the ones that are part of the chain with bValid = true
            while (true)
            {
                // Mark it as a valid sub-state
                txState.persistence[persistence].subState[currentSubState].bValid = true;

                // If we went back to the first sub-state, we are done, as long as the old state roots match
                if (currentSubState == 0)
                {
                    // Check that both old state roots match
                    if (txState.persistence[persistence].subState[currentSubState].oldStateRoot != txState.persistence[persistence].oldStateRoot)
                    {
                        zklog.error("StateManager64::flush() found inconsistent old state roots: batchUUID=" + batchUUID +
                                    " tx=" + to_string(tx) + " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString() +
                                    " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                                    " substate.oldStateRoot=" + txState.persistence[persistence].subState[currentSubState].oldStateRoot.toString());

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                        batchState.timeMetricStorage.add("flush UUID inconsistent old state roots", TimeDiff(t));
                        batchState.timeMetricStorage.print("State Manager calls");
#endif
                        Unlock();
                        return ZKR_STATE_MANAGER;
                    }

                    // We are done
                    break;
                }

                // If the previous sub-state ended the same way this sub-state started, then it is part of the chain
                uint64_t previousSubState = txState.persistence[persistence].subState[currentSubState].previousSubState;
                if (txState.persistence[persistence].subState[previousSubState].newStateRoot == txState.persistence[persistence].subState[currentSubState].oldStateRoot)
                {
                    currentSubState = previousSubState;
                    continue;
                }

                // Otherwise, we resumed the chain from a previous state, maybe due to a revert
                // Search for the previous state that ends the same way this sub-state starts
                uint64_t i = 0;
                for (; i < currentSubState; i++)
                {
                    if (txState.persistence[persistence].subState[i].newStateRoot == txState.persistence[persistence].subState[currentSubState].oldStateRoot)
                    {
                        previousSubState = i;
                        break;
                    }
                }

                // Check that we actually found it
                if (i == currentSubState)
                {
                    zklog.error("StateManager64::flush() could not find previous tx sub-state: batchUUID=" + batchUUID +
                                " tx=" + to_string(tx) +
                                " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString() +
                                " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                                " substate.oldStateRoot=" + txState.persistence[persistence].subState[currentSubState].oldStateRoot.toString());
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                    batchState.timeMetricStorage.add("flush UUID cannot find previous tx sub-state", TimeDiff(t));
                    batchState.timeMetricStorage.print("State Manager calls");
#endif
                    Unlock();
                    return ZKR_STATE_MANAGER;
                }

                // Iterate with the previous state
                currentSubState = previousSubState;
            }

            // Delete invalid TX sub-states, i.e. the ones with bValid = false
            if (db.config.stateManagerPurge)
            {
                // Delete all substates that are not valid or that did not change the state root (i.e. SMT set update in which new value was equal to old value)
                for (int64_t i = txState.persistence[persistence].subState.size() - 1; i >= 0; i--)
                {
                    if (!txState.persistence[persistence].subState[i].bValid ||
                        (txState.persistence[persistence].subState[i].oldStateRoot == txState.persistence[persistence].subState[i].newStateRoot))
                    {
                        txState.persistence[persistence].subState.erase(txState.persistence[persistence].subState.begin() + i);
                    }
                }
            }

            // Save data to database

            // For all sub-states
            /*for (uint64_t ss = 0; ss < txState.persistence[persistence].subState.size(); ss++)
            {
                // For all keys to write
                unordered_map<string, mpz_class>::const_iterator writeIt;
                for (writeIt = txState.persistence[persistence].subState[ss].dbWrite.begin();
                     writeIt != txState.persistence[persistence].subState[ss].dbWrite.end();
                     writeIt++)
                {
                    // TODO: write all key-values at once
                    // zkr = db.write(writeIt->first, NULL, writeIt->second, persistence == PERSISTENCE_DATABASE ? 1 : 0);
                    zkr = ZKR_SUCCESS;
                    if (zkr != ZKR_SUCCESS)
                    {
                        zklog.error("StateManager64::flush() failed calling db.write() result=" + zkresult2string(zkr));
                        state.erase(it);

                        TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                        batchState.timeMetricStorage.add("flush error db.write", TimeDiff(t));
                        batchState.timeMetricStorage.print("State Manager calls");
#endif
                        Unlock();
                        return zkr;
                    }
                }
            }*/

            /*if (persistence == PERSISTENCE_DATABASE)
            {
                if (txState.persistence[persistence].newStateRoot.realStateRoot.size() == 0)
                {
                    zklog.error("StateManager64::flush() failed txState.persistence[persistence].newStateRoot.realStateRoot.size()=0");
                    state.erase(it);

                    TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                    batchState.timeMetricStorage.add("flush error realStateRoot.size", TimeDiff(t));
                    batchState.timeMetricStorage.print("State Manager calls");
#endif
                    Unlock();
                    return zkr;
                }
                vector<Goldilocks::Element> fea;
                string2fea(db.fr, txState.persistence[persistence].newStateRoot.realStateRoot, fea);
                if (fea.size() != 4)
                {
                    zklog.error("StateManager64::flush() failed calling string2fea() fea.size=" + to_string(fea.size()));
                    state.erase(it);

                    TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                    batchState.timeMetricStorage.add("flush error string2fea", TimeDiff(t));
                    batchState.timeMetricStorage.print("State Manager calls");
#endif
                    Unlock();
                    return zkr;
                }
                Goldilocks::Element newStateRootFea[4];
                newStateRootFea[0] = fea[3];
                newStateRootFea[1] = fea[2];
                newStateRootFea[2] = fea[1];
                newStateRootFea[3] = fea[0];

                zkr = db.updateStateRoot(newStateRootFea);
                if (zkr != ZKR_SUCCESS)
                {
                    zklog.error("StateManager64::flush() failed calling db.updateStateRoot() result=" + zkresult2string(zkr));
                    state.erase(it);

                    TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                    batchState.timeMetricStorage.add("flush error db.updateStateRoot", TimeDiff(t));
                    batchState.timeMetricStorage.print("State Manager calls");
#endif
                    Unlock();
                    return zkr;
                }
            }*/

            // Get old state root for this tx
            Goldilocks::Element oldRoot[4];
            string2fea(fr, txState.persistence[persistence].oldStateRoot.realStateRoot, oldRoot);

            // Get the key-values for this tx
            vector<KeyValue> keyValues;
            unordered_map<string, mpz_class> &dbWrite = txState.persistence[persistence].subState[txState.persistence[persistence].subState.size() - 1].dbWrite;
            unordered_map<string, mpz_class>::const_iterator it;
            for (it = dbWrite.begin(); it != dbWrite.end(); it++)
            {
                KeyValue keyValue;
                string2fea(fr, it->first, keyValue.key.fe);
                keyValue.value = it->second;
                keyValues.emplace_back(keyValue);
            }

            // Call WriteTree and get the new state root
            Goldilocks::Element newRoot[4];
            zkr = tree64.WriteTree(db, oldRoot, keyValues, newRoot, persistence == PERSISTENCE_DATABASE ? true : false);
            if (zkr != ZKR_SUCCESS)
            {
                zklog.error("StateManager64::flush() failed calling WriteTree zkr=" + zkresult2string(zkr) +
                            " tx=" + to_string(tx) +
                            " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString());
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("WriteTree failed", TimeDiff(t));
                batchState.timeMetricStorage.print("State Manager calls");
#endif
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Save the real state root of this tx
            string newRootString = fea2string(fr, newRoot);
            txState.persistence[persistence].newStateRoot.realStateRoot = newRootString;

            // Save the old state root of the next tx, if any
            if (tx < batchState.txState.size() - 1)
            {
                zkassertpermanent(batchState.txState[tx+1].persistence[persistence].oldStateRoot.realStateRoot.size() == 0);
                batchState.txState[tx+1].persistence[persistence].oldStateRoot.realStateRoot = newRootString;
            }
            // If this is the last tx, then save the new state root of the batch
            else
            {
                batchState.newStateRoot.realStateRoot = newRootString;
            }

            // Create a new version
            uint64_t version;
            zkr = db.createLatestVersion(version, persistence == PERSISTENCE_DATABASE ? true : false);
            if (zkr != ZKR_SUCCESS)
            {
                zklog.error("StateManager64::flush() failed calling db.createLatestVersion zkr=" + zkresult2string(zkr) +
                            " tx=" + to_string(tx) +
                            " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString());
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("db.createLatestVersion failed", TimeDiff(t));
                batchState.timeMetricStorage.print("State Manager calls");
#endif
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Save the key-values
            zkr = db.writeKV(version, keyValues, persistence == PERSISTENCE_DATABASE ? true : false);
            if (zkr != ZKR_SUCCESS)
            {
                zklog.error("StateManager64::flush() failed calling db.writeKV zkr=" + zkresult2string(zkr) +
                            " tx=" + to_string(tx) +
                            " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString());
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("db.writeKV failed", TimeDiff(t));
                batchState.timeMetricStorage.print("State Manager calls");
#endif
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Write the new version, associated with the new root
            zkr = db.writeVersion(newRoot, version, persistence == PERSISTENCE_DATABASE ? true : false);
            if (zkr != ZKR_SUCCESS)
            {
                zklog.error("StateManager64::flush() failed calling db.writeVersion zkr=" + zkresult2string(zkr) +
                            " tx=" + to_string(tx) +
                            " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString());
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("db.writeVersion failed", TimeDiff(t));
                batchState.timeMetricStorage.print("State Manager calls");
#endif
                Unlock();
                return ZKR_STATE_MANAGER;
            }

        } // For all persistences

    } // For all transactions

    zkr = db.flush(flushId, lastSentFlushId);
    if (zkr != ZKR_SUCCESS)
    {
        zklog.error("StateManager64::flush() failed calling db.flush() result=" + zkresult2string(zkr));
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("flush success", TimeDiff(t));
    batchState.timeMetricStorage.print("State Manager calls");
#endif

    // Delete this batch UUID state
    state.erase(it);

    Unlock();

    TimerStopAndLog(STATE_MANAGER_FLUSH);

    return zkr;
}

void StateManager64::print(bool bDbContent)
{
    uint64_t totalDbWrites[PERSISTENCE_SIZE] = {0, 0, 0};
    zklog.info("StateManager64::print():");
    zklog.info("state.size=" + to_string(state.size()));
    unordered_map<string, BatchState64>::const_iterator stateIt;
    uint64_t batchStateCounter = 0;
    for (stateIt = state.begin(); stateIt != state.end(); stateIt++)
    {
        const BatchState64 &batchState = stateIt->second;
        zklog.info("  batchState=" + to_string(batchStateCounter));
        batchStateCounter++;
        zklog.info("  BatchUUID=" + stateIt->first);
        zklog.info("  oldStateRoot=" + batchState.oldStateRoot.toString());
        zklog.info("  currentStateRoot=" + batchState.currentStateRoot.toString());
        zklog.info("  currentTx=" + to_string(batchState.currentTx));

        for (uint64_t tx = 0; tx < batchState.txState.size(); tx++)
        {

            zklog.info("    TX=" + to_string(tx));
            const TxState64 &txState = batchState.txState[tx];

            for (uint64_t persistence = 0; persistence < PERSISTENCE_SIZE; persistence++)
            {
                zklog.info("      persistence=" + to_string(persistence) + "=" + persistence2string((Persistence)persistence));
                zklog.info("        oldStateRoot=" + txState.persistence[persistence].oldStateRoot.toString());
                zklog.info("        newStateRoot=" + txState.persistence[persistence].newStateRoot.toString());
                zklog.info("        currentSubState=" + to_string(txState.persistence[persistence].currentSubState));
                zklog.info("        txSubState.size=" + to_string(txState.persistence[persistence].subState.size()));
                for (uint64_t i = 0; i < txState.persistence[persistence].subState.size(); i++)
                {
                    const TxSubState64 &txSubState = txState.persistence[persistence].subState[i];
                    zklog.info("          txSubState=" + to_string(i));
                    zklog.info("            oldStateRoot=" + txSubState.oldStateRoot.toString());
                    zklog.info("            newStateRoot=" + txSubState.newStateRoot.toString());
                    zklog.info("            valid=" + to_string(txSubState.bValid));
                    zklog.info("            previousSubState=" + to_string(txSubState.previousSubState));
                    zklog.info("            dbWrite.size=" + to_string(txSubState.dbWrite.size()));

                    totalDbWrites[persistence] += txSubState.dbWrite.size();
                    if (bDbContent)
                    {
                        unordered_map<string, mpz_class>::const_iterator dbIt;
                        for (dbIt = txSubState.dbWrite.begin(); dbIt != txSubState.dbWrite.end(); dbIt++)
                        {
                            zklog.info("              key=" + dbIt->first + " value=" + dbIt->second.get_str(16));
                        }
                    }
                }
            }
        }
    }

    uint64_t totalWrites = 0;
    for (uint64_t persistence = 0; persistence < PERSISTENCE_SIZE; persistence++)
    {
        zklog.info("total db writes[" + persistence2string((Persistence)persistence) + "]=" + to_string(totalDbWrites[persistence]));
        totalWrites += totalDbWrites[persistence];
    }
    zklog.info("total writes=" + to_string(totalWrites));
}

void StateManager64::getVirtualStateRoot(Goldilocks::Element (&newStateRoot)[4], string &newStateRootString)
{
    lastVirtualStateRoot++;
    Goldilocks::Element fea[12];
    fea[0] = fr.fromU64(lastVirtualStateRoot);
    for (uint64_t i = 1; i < 12; i++)
    {
        fea[i] = fr.zero();
    }
    poseidon.hash(newStateRoot, fea);
    newStateRootString = NormalizeToNFormat(fea2string(fr, newStateRoot), 64);
    lastVirtualStateRootString = newStateRootString;
    virtualStateRoots[newStateRootString] = lastVirtualStateRoot;
}

bool StateManager64::isVirtualStateRoot(const string &stateRoot)
{
    if (lastVirtualStateRootString == stateRoot)
    {
        return true;
    }
    else if (virtualStateRoots.find(stateRoot) != virtualStateRoots.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}