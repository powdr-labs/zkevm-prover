#include "state_manager.hpp"
#include "zkassert.hpp"
#include "zklog.hpp"
#include "scalar.hpp"
#include "timer.hpp"
#include "persistence.hpp"
#include "definitions.hpp"

// Singleton definition
StateManager stateManager;

//#define LOG_STATE_MANAGER
//#define LOG_STATE_MANAGER_READ
//#define LOG_STATE_MANAGER_WRITE
//#define LOG_STATE_MANAGER_DELETE_NODE

zkresult StateManager::setStateRoot (const string &batchUUID, uint64_t block, uint64_t tx, const string &_stateRoot, bool bIsOldStateRoot, const Persistence persistence)
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
        zklog.error("StateManager::setStateRoot() invalid persistence batchUUID=" + batchUUID + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::setStateRoot() batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState>::iterator it;

    // Find batch state for this uuid, or create it if it does not exist
    it = state.find(batchUUID);
    if (it == state.end())
    {
        if (!bIsOldStateRoot)
        {
            zklog.error("StateManager::setStateRoot() called with bIsOldStateRoot=false, but batchUUID=" + batchUUID + " does not previously exist");
            Unlock();
            return ZKR_STATE_MANAGER;
        }
        BatchState batchState;
        state[batchUUID] = batchState;
        it = state.find(batchUUID);
        zkassert(it != state.end());
    }
    BatchState &batchState = it->second;

    // The first time we set a non-temporary old state root, assign it to the batch old state root
    if ( batchState.oldStateRoot.empty() &&
         ((persistence == PERSISTENCE_DATABASE) || (persistence == PERSISTENCE_CACHE)) &&
         bIsOldStateRoot )
    {
        batchState.oldStateRoot = stateRoot;
    }

    // Set the current state root
    batchState.currentStateRoot = stateRoot;

    // Check block range
    if (block >= batchState.blockState.size())
    {
        zklog.error("StateManager::setStateRoot() called with block=" + to_string(block) + " but blockState.size=" + to_string(batchState.blockState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Get a reference to the block state
    BlockState &blockState = batchState.blockState[block];

    // The first time we set a non-temporary old state root, assign it to the block old state root
    if ( blockState.oldStateRoot.empty() &&
         ((persistence == PERSISTENCE_DATABASE) || (persistence == PERSISTENCE_CACHE)) &&
         bIsOldStateRoot )
    {
        blockState.oldStateRoot = stateRoot;
    }

    // Create tx states, if needed
    if (tx >= blockState.txState.size())
    {
        // If this is the first state of a new tx, check that it is the old state root
        if (!bIsOldStateRoot)
        {
            zklog.error("StateManager::setStateRoot() called with bIsOldStateRoot=false, but tx=" + to_string(tx) + " does not previously exist");
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Calculate the number of tx slots to create
        uint64_t txsToCreate = tx - blockState.txState.size() + 1;

        // Create TX state to insert
        TxState txState;
        
        // Insert TX state
        for (uint64_t i=0; i<txsToCreate; i++)
        {
            blockState.txState.emplace_back(txState);
        }

        // Set current TX
        blockState.currentTx = tx;
    }

    // Get a reference to the tx state
    TxState &txState = blockState.txState[tx];

    // Get the current sub-state list size
    uint64_t currentSubStateSize = txState.persistence[persistence].subState.size();
    
    // In case it is an old state root, we need to create a new sub-state, and check that everything makes sense
    if (bIsOldStateRoot)
    {
        // If this is the first sub-state of the tx state, record the tx old state root
        if ( currentSubStateSize == 0)
        {
            // Check current sub-state
            if (txState.persistence[persistence].currentSubState != 0)
            {
                zklog.error("StateManager::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + "!=0 batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Record the old state root
            txState.persistence[persistence].oldStateRoot = stateRoot;
        }

        // If it is not the first sub-state, it must have been called with the previous new state root
        else
        {
            // Check current sub-state
            if (txState.persistence[persistence].currentSubState >= currentSubStateSize)
            {
                zklog.error("StateManager::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + " > currentSubStateSize=" + to_string(currentSubStateSize) + " batchUUID=" + batchUUID + " block=" + to_string(block) +  " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Check that new state root is empty
            if (txState.persistence[persistence].subState[currentSubStateSize-1].newStateRoot.size() == 0)
            {
                zklog.error("StateManager::setStateRoot() oldStateRoot found previous newStateRoot empty");
                Unlock();
                return ZKR_STATE_MANAGER;
            }
        }

        // Create TX sub-state
        TxSubState txSubState;
        txSubState.oldStateRoot = stateRoot;
        txSubState.previousSubState = txState.persistence[persistence].currentSubState;

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
            zklog.error("StateManager::setStateRoot() currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + " > currentSubStateSize=" + to_string(currentSubStateSize) + " batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " stateRoot=" + stateRoot + " bIsOldStateRoot=" + to_string(bIsOldStateRoot) + " persistence=" + persistence2string(persistence));
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Check that the new state root is empty
        if (txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot.size() != 0)
        {
            zklog.error("StateManager::setStateRoot() found nesStateRoot busy");
            Unlock();
            return ZKR_STATE_MANAGER;
        }

        // Record the new state root in the tx sub-state, and in the tx state
        txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot = stateRoot;
        txState.persistence[persistence].newStateRoot = stateRoot;
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("setStateRoot", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;

}

zkresult StateManager::writeNode (const string &batchUUID, uint64_t block, uint64_t tx, const string &_key, const vector<Goldilocks::Element> &value, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

#ifdef LOG_STATE_MANAGER_WRITE
    zklog.info("StateManager::writeNode() batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
#endif

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager::writeNode() wrong persistence batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.error("StateManager::writeNode() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BatchState &batchState = it->second;

    // Check block range
    if (block >= batchState.blockState.size())
    {
        zklog.error("StateManager::writeNode() got block=" + to_string(block) + " bigger than blockState size=" + to_string(it->second.blockState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BlockState &blockState = batchState.blockState[block];

    // Check tx range
    if (tx > blockState.txState.size())
    {
        zklog.error("StateManager::writeNode() got tx=" + to_string(tx) + " bigger than txState size=" + to_string(blockState.txState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Create TxState, if not existing
    if (tx == blockState.txState.size())
    {
        TxState aux;
        aux.persistence[persistence].oldStateRoot = it->second.currentStateRoot;
        blockState.txState.emplace_back(aux);
    }
    TxState &txState = blockState.txState[tx];

    // Create TxSubState, if not existing
    if (txState.persistence[persistence].subState.size() == 0)
    {
        TxSubState subState;
        subState.previousSubState = 0;
        subState.oldStateRoot = batchState.currentStateRoot;
        txState.persistence[persistence].subState.emplace_back(subState);
        txState.persistence[persistence].currentSubState = 0;
    }

    // Add to sub-state
    txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].dbWriteNodes[key] = value;
    
    // Add to common write pool to speed up read
    batchState.dbWriteNodes[key] = value;

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("writeNode", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::deleteNode (const string &batchUUID, uint64_t block, uint64_t tx, const string &_key, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

#ifdef LOG_STATE_MANAGER_DELETE_NODE
    zklog.info("StateManager::deleteNode() batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
#endif

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager::deleteNode() invalid persistence batchUUID=" + batchUUID + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

    Lock();

    unordered_map<string, BatchState>::iterator it;

    // Find batch state for this batch uuid
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.error("StateManager::deleteNode() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BatchState &batchState = it->second;

    // Check block range
    if (block >= batchState.blockState.size())
    {
        zklog.error("StateManager::deleteNode() got block=" + to_string(block) + " bigger than blockState size=" + to_string(batchState.blockState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Find block state for this block
    BlockState &blockState = batchState.blockState[block];

    // Check tx range
    if (tx >= blockState.txState.size())
    {
        zklog.error("StateManager::deleteNode() got tx=" + to_string(tx) + " bigger than txState size=" + to_string(blockState.txState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Find TX state for this tx
    TxState &txState = blockState.txState[tx];
    
    // Find TX current sub-state
    if (txState.persistence[persistence].subState.size() == 0)
    {
        zklog.error("StateManager::deleteNode() found subState.size=0 tx=" + to_string(tx) + " batchUUIDe=" + batchUUID);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    if (txState.persistence[persistence].currentSubState >= txState.persistence[persistence].subState.size())
    {
        zklog.error("StateManager::deleteNode() found currentSubState=" + to_string(txState.persistence[persistence].currentSubState) + " >= subState.size=" + to_string(txState.persistence[persistence].subState.size()) + " tx=" + to_string(tx) + " batchUUIDe=" + batchUUID);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    TxSubState &txSubState = txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState];

    // Delete this key in the surrent TX sub-state
    /*unordered_map<string, vector<Goldilocks::Element>>::iterator dbIt;
    dbIt = txSubState.dbWrite.find(key);
    if (dbIt != txSubState.dbWrite.end())
    {
        txSubState.dbWrite.erase(dbIt);
        zklog.info("StateManager::deleteNode() batchUUID=" + batchUUID + " tx=" + to_string(tx) + " key=" + key);
    }*/

    txSubState.dbDeleteNodes.emplace_back(key);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("deleteNode", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::readNode (const string &batchUUID, const string &_key, vector<Goldilocks::Element> &value, DatabaseMap *dbReadLog)
{
    struct timeval t;
    gettimeofday(&t, NULL);

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        //zklog.error("StateManager::read() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_DB_KEY_NOT_FOUND;
    }
    BatchState &batchState = it->second;

    // Search in the common write list
    unordered_map<string, vector<Goldilocks::Element>>::iterator dbIt;
    dbIt = batchState.dbWriteNodes.find(key);
    if (dbIt != batchState.dbWriteNodes.end())
    {
        value = dbIt->second;
                        
        // Add to the read log
        if (dbReadLog != NULL) dbReadLog->add(key, value, true, TimeDiff(t));

#ifdef LOG_STATE_MANAGER_READ
        zklog.info("StateManager::readNode() batchUUID=" + batchUUID + " key=" + key);
#endif

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        batchState.timeMetricStorage.add("readNode success", TimeDiff(t));
#endif
        Unlock();

        return ZKR_SUCCESS;
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("readNode not found", TimeDiff(t));
#endif

    Unlock();

    return ZKR_DB_KEY_NOT_FOUND;
}

zkresult StateManager::writeProgram (const string &batchUUID, uint64_t block, uint64_t tx, const string &_key, const vector<uint8_t> &value, const Persistence persistence)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

#ifdef LOG_STATE_MANAGER_WRITE
    zklog.info("StateManager::writeProgram() batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
#endif

    // Check persistence range
    if (persistence >= PERSISTENCE_SIZE)
    {
        zklog.error("StateManager::writeProgram() wrong persistence batchUUID=" + batchUUID + " block=" + to_string(block) + " tx=" + to_string(tx) + " key=" + key + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

    Lock();

    // Find batch state for this uuid, or create it if it does not exist
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        BatchState batchState;
        state[batchUUID] = batchState;
        it = state.find(batchUUID);
        zkassert(it != state.end());
    }
    BatchState &batchState = it->second;

    // Detect first set programs before first block, one per TX, and ignore them
    if ((block == 0) && batchState.blockState.empty())
    {
        //zklog.warning("StateManager::writeProgram() ignoring program set before first block key=" + key);
        Unlock();
        return ZKR_SUCCESS;
    }

    // Check block range
    if (block >= batchState.blockState.size())
    {
        zklog.error("StateManager::writeProgram() got block=" + to_string(block) + " bigger than blockState size=" + to_string(it->second.blockState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BlockState &blockState = batchState.blockState[block];

    // Check tx range
    if (tx > blockState.txState.size())
    {
        zklog.error("StateManager::writeProgram() got tx=" + to_string(tx) + " bigger than txState size=" + to_string(blockState.txState.size()));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Create TxState, if not existing
    if (tx == blockState.txState.size())
    {
        TxState aux;
        aux.persistence[persistence].oldStateRoot = it->second.currentStateRoot;
        blockState.txState.emplace_back(aux);
    }
    TxState &txState = blockState.txState[tx];

    // Add to sub-state
    txState.persistence[persistence].dbWritePrograms[key] = value;
    
    // Add to common write pool to speed up read
    batchState.dbWritePrograms[key] = value;

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("writePrograms", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::readProgram (const string &batchUUID, const string &_key, vector<uint8_t> &value, DatabaseMap *dbReadLog)
{
    struct timeval t;
    gettimeofday(&t, NULL);

    // Normalize key format
    string key = NormalizeToNFormat(_key, 64);
    key = stringToLower(key);

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        //zklog.error("StateManager::readProgram() found no batch state for batch UUID=" + batchUUID);
        Unlock();
        return ZKR_DB_KEY_NOT_FOUND;
    }
    BatchState &batchState = it->second;

    // Search in the common write list
    unordered_map<string, vector<uint8_t>>::iterator dbIt;
    dbIt = batchState.dbWritePrograms.find(key);
    if (dbIt != batchState.dbWritePrograms.end())
    {
        value = dbIt->second;
                        
        // Add to the read log
        if (dbReadLog != NULL) dbReadLog->add(key, value, true, TimeDiff(t));

#ifdef LOG_STATE_MANAGER_READ
        zklog.info("StateManager::readProgram() batchUUID=" + batchUUID + " key=" + key);
#endif

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        batchState.timeMetricStorage.add("readProgram success", TimeDiff(t));
#endif
        Unlock();

        return ZKR_SUCCESS;
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("readProgram not found", TimeDiff(t));
#endif

    Unlock();

    return ZKR_DB_KEY_NOT_FOUND;
}

bool IsInvalid(TxSubState &txSubState)
{
    return !txSubState.bValid;
}

zkresult StateManager::finishTx (const string &batchUUID, const string &_stateRoot, const Persistence persistence)
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
        zklog.error("StateManager::finishTx() invalid persistence batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::finishTx() batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState>::iterator it;

    // Find batch state for this uuid
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.warning("StateManager::finishTx() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");
 
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        //batchState.timeMetricStorage.add("finishTx UUID not found", TimeDiff(t));
        //batchState.timeMetricStorage.print("State Manager calls");
#endif
        Unlock();
        return ZKR_SUCCESS;
    }
    BatchState &batchState = it->second;

    // Check currentBlock range
    if (batchState.currentBlock >= batchState.blockState.size())
    {
        zklog.error("StateManager::finishTx() found batchState.currentBlock=" + to_string(batchState.currentBlock) + " >= batchState.blockState.size=" + to_string(batchState.blockState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BlockState &blockState = batchState.blockState[batchState.currentBlock];

    // Check currentTx range
    if (blockState.currentTx >= blockState.txState.size())
    {
        zklog.error("StateManager::finishTx() found blockState.currentTx=" + to_string(blockState.currentTx) + " >= blockState.txState.size=" + to_string(blockState.txState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Get a reference to the tx state
    TxState &txState = blockState.txState[blockState.currentTx];
    TxPersistenceState &txPersistenceState = txState.persistence[persistence];

    if (txPersistenceState.newStateRoot == stateRoot)
    {
        // This is the expected case
    }
    else if (txPersistenceState.oldStateRoot == stateRoot)
    {
        if (config.stateManagerPurge)
        {
            // The TX ended up with the same state root as the beginning, so we can delete all data
            txPersistenceState.subState.clear();
            txPersistenceState.newStateRoot = stateRoot;
            txPersistenceState.currentSubState = 0;
        }
    }
    else
    {
        if (config.stateManagerPurge)
        {
            // Search for the point at which we reach this state, and delete the rest
            bool bFound = false;
            uint64_t i=0;
            uint64_t subStateSize = txPersistenceState.subState.size();
            for (i=0; i<subStateSize; i++)
            {
                if (!bFound && txPersistenceState.subState[i].oldStateRoot == stateRoot)
                {
                    bFound = true;
                    break;
                }
            }
            if (bFound)
            {
                txPersistenceState.newStateRoot = stateRoot;
                txPersistenceState.currentSubState = (i == 0) ? 0 : i-1;
                for (; i<subStateSize; i++)
                {
                    txPersistenceState.subState.pop_back();
                }
            }
        }
    }
    
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("finishTx", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::startBlock (const string &batchUUID, const string &_stateRoot, const Persistence persistence)
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
        zklog.error("StateManager::startBlock() invalid persistence batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::startBlock() batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState>::iterator it;

    // Find batch state for this uuid
    it = state.find(batchUUID);
    if (it == state.end())
    {
        BatchState batchState;
        state[batchUUID] = batchState;
        it = state.find(batchUUID);
        zkassert(it != state.end());
    }
    BatchState &batchState = it->second;

    // Check currentBlock range
    if (!batchState.blockState.empty() && (batchState.currentBlock >= batchState.blockState.size()))
    {
        zklog.error("StateManager::startBlock() found batchState.currentBlock=" + to_string(batchState.currentBlock) + " >= batchState.blockState.size=" + to_string(batchState.blockState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Create an empty block state to insert
    BlockState blockState;
    blockState.oldStateRoot = stateRoot;
    batchState.blockState.emplace_back(blockState);

    // Set current block
    batchState.currentBlock = batchState.blockState.size() - 1;
    
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("startBlock", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::finishBlock (const string &batchUUID, const string &_stateRoot, const Persistence persistence)
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
        zklog.error("StateManager::finishBlock() invalid persistence batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        return ZKR_STATE_MANAGER;
    }

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::finishBlock() batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
#endif

    Lock();

    unordered_map<string, BatchState>::iterator it;

    // Find batch state for this uuid
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.warning("StateManager::finishBlock() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");
 
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        //batchState.timeMetricStorage.add("finishBlock UUID not found", TimeDiff(t));
        //batchState.timeMetricStorage.print("State Manager calls");
#endif
        Unlock();
        return ZKR_SUCCESS;
    }
    BatchState &batchState = it->second;

    // Check currentBlock range
    if (batchState.currentBlock >= batchState.blockState.size())
    {
        zklog.error("StateManager::finishBlock() found batchState.currentBlock=" + to_string(batchState.currentBlock) + " >= batchState.blockState.size=" + to_string(batchState.blockState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    BlockState &blockState = batchState.blockState[batchState.currentBlock];

    // Check currentTx range
    if (blockState.currentTx >= blockState.txState.size())
    {
        zklog.error("StateManager::finishBlock() found blockState.currentTx=" + to_string(blockState.currentTx) + " >= blockState.txState.size=" + to_string(blockState.txState.size()) + " batchUUID=" + batchUUID + " stateRoot=" + stateRoot + " persistence=" + persistence2string(persistence));
        Unlock();
        return ZKR_STATE_MANAGER;
    }

    // Get a reference to the tx state
    TxState &txState = blockState.txState[blockState.currentTx];
    TxPersistenceState &txPersistenceState = txState.persistence[persistence];


    // This is the happy path case: the last tx
    if (txPersistenceState.newStateRoot == stateRoot)
    {
        blockState.currentStateRoot = stateRoot;
    }

    // If it ended with the same state, activity can be discarded
    else if (txPersistenceState.oldStateRoot == stateRoot)
    {
        if (config.stateManagerPurge)
        {
            // The block ended up with the same state root as the beginning, so we can delete all data
            blockState.txState.clear();
            blockState.currentStateRoot = stateRoot;
            blockState.currentTx = 0;
        }
    }
    else
    {
        if (config.stateManagerPurge)
        {
            // Search for the point at which we reach this state, and delete the rest
            bool bFound = false;
            uint64_t i=0;
            uint64_t txStateSize = blockState.txState.size();
            for (i=0; i<txStateSize; i++)
            {
                if (!bFound && blockState.txState[i].persistence[persistence].oldStateRoot == stateRoot)
                {
                    bFound = true;
                    break;
                }
            }
            if (bFound)
            {
                blockState.currentStateRoot = stateRoot;
                blockState.currentTx = (i == 0) ? 0 : i-1;
                for (; i<txStateSize; i++)
                {
                    blockState.txState.pop_back();
                }
            }
        }
    }
    
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("finishBlock", TimeDiff(t));
#endif

    Unlock();

    return ZKR_SUCCESS;
}

zkresult StateManager::flush (const string &batchUUID, const string &_newStateRoot, const Persistence _persistence, Database &db, uint64_t &flushId, uint64_t &lastSentFlushId)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t, t2;
    gettimeofday(&t, NULL);
#endif

    string newStateRoot = NormalizeToNFormat(_newStateRoot, 64);

    //TimerStart(STATE_MANAGER_FLUSH);

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::flush() batchUUID=" + batchUUID + " newStateRoot=" + newStateRoot + " persistence=" + persistence2string(_persistence));
#endif

    // For every TX, track backwards from newStateRoot to oldStateRoot, marking sub-states as valid

    Lock();

    zkresult zkr;

    //print(false);

    // Find batch state for this uuid
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        //zklog.warning("StateManager::flush() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");
 
        zkr = db.flush(flushId, lastSentFlushId);
        if (zkr != ZKR_SUCCESS)
        {
            zklog.error("StateManager::flush() failed calling db.flush() result=" + zkresult2string(zkr));
        }

        //TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        //timeMetricStorage.add("flush UUID not found", TimeDiff(t));
        //timeMetricStorage.print("State Manager calls");
#endif
        Unlock();
        return zkr;
    }
    BatchState &batchState = it->second;

    /////////////////////////////////////////////////
    // Purge batch, i.e. delete unnecessary blocks //
    /////////////////////////////////////////////////

    if (config.stateManagerPurge && !_newStateRoot.empty() && !batchState.blockState.empty() && !batchState.oldStateRoot.empty())
    {

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        gettimeofday(&t2, NULL);
#endif

        // Search for the first block that starts at the new state root
        uint64_t firstBlock;
        bool firstBlockFound = false;
        for (firstBlock = 0; firstBlock < batchState.blockState.size(); firstBlock++)
        {
            if (batchState.blockState[firstBlock].oldStateRoot == newStateRoot)
            {
                firstBlockFound = true;
                break;
            }
        }

        // If we found it
        if (firstBlockFound)
        {
            // Delete this block, and the next blocks
            while (batchState.blockState.size() > firstBlock)
            {
                batchState.blockState.pop_back();
            }
        }

        // Search for the last block that ends at the new state root
        if (!batchState.blockState.empty())
        {
            int64_t lastBlock;
            bool lastBlockFound = false;
            for (lastBlock = (batchState.blockState.size() - 1); lastBlock >= 0; lastBlock--)
            {
                if (batchState.blockState[lastBlock].currentStateRoot == newStateRoot)
                {
                    lastBlockFound = true;
                    break;
                }
            }
            if (!lastBlockFound)
            {
                zklog.error("StateManager::flush() could not find a block state that ends with newStateRoot=" + newStateRoot + " batchUUID=" + batchUUID);
                Unlock();
                return ZKR_STATE_MANAGER;
            }

            // Delete all previous blocks not belonging to the state root chain
            string currentStateRoot = batchState.blockState[lastBlock].oldStateRoot;
            for (int64_t block = lastBlock - 1; block >= 0; block--)
            {
                if (batchState.blockState[block].currentStateRoot == currentStateRoot)
                {
                    currentStateRoot = batchState.blockState[block].oldStateRoot;
                    continue;
                }
                batchState.blockState.erase(batchState.blockState.begin() + block);
            }

            // Check that we reached the expected batch old state root
            if (batchState.blockState[0].oldStateRoot != batchState.oldStateRoot)
            {
                zklog.error("StateManager::flush() could not find a block state that starts with oldStateRoot=" + batchState.oldStateRoot + " batchUUID=" + batchUUID);
                Unlock();
                return ZKR_STATE_MANAGER;
            }
        }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        batchState.timeMetricStorage.add("purge blocks", TimeDiff(t2));
#endif
    }

    // Data to write to database
    unordered_map<string, vector<Goldilocks::Element>> dbWriteNodes;
    string lastNewStateRoot;

    // For all blocks
    for (uint64_t block=0; block<batchState.blockState.size(); block++)
    {
        BlockState &blockState = batchState.blockState[block];

        // For all tx sub-states, purge the data to write
        for (uint64_t tx=0; tx<blockState.txState.size(); tx++)
        {
            for (uint64_t persistence = 0; persistence < PERSISTENCE_SIZE; persistence++)
            {
                TxState &txState = blockState.txState[tx];

                // Temporary data can be deleted at the end of a batch
                if ((persistence == PERSISTENCE_TEMPORARY) || (persistence == PERSISTENCE_TEMPORARY_HASH))
                {
                    txState.persistence[persistence].subState.clear();
                    txState.persistence[persistence].currentSubState = 0;
                    continue;
                }

                // If there's no data, there's nothing to do
                if (txState.persistence[persistence].subState.size() == 0)
                {
                    continue;
                }

                // Check that current sub-state newStateRoot matches the TX one
                if (txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot != txState.persistence[persistence].newStateRoot)
                {
                    zklog.error("StateManager::flush() found inconsistent new state roots: batchUUID=" + batchUUID +
                        " newStateRoot=" + _newStateRoot +
                        " block=" + to_string(block) +
                        " tx=" + to_string(tx) + " txState.newStateRoot=" + txState.persistence[persistence].newStateRoot +
                        " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                        " substate.newStateRoot=" + txState.persistence[persistence].subState[txState.persistence[persistence].currentSubState].newStateRoot);
                        
    #ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                    batchState.timeMetricStorage.add("flush UUID inconsistent new state roots", TimeDiff(t));
                    batchState.timeMetricStorage.print("State Manager calls");
    #endif
                    Unlock();
                    return ZKR_STATE_MANAGER;
                }

                //////////////////////////
                // Find valid substates //
                //////////////////////////

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                gettimeofday(&t2, NULL);
#endif
                uint64_t currentSubState = txState.persistence[persistence].currentSubState;
                while (true)
                {
                    txState.persistence[persistence].subState[currentSubState].bValid = true;
                    if (currentSubState == 0)
                    {
                        if (txState.persistence[persistence].subState[currentSubState].oldStateRoot != txState.persistence[persistence].oldStateRoot)
                        {
                            zklog.error("StateManager::flush() found inconsistent old state roots: batchUUID=" + batchUUID +
                                " newStateRoot=" + _newStateRoot +
                                " block=" + to_string(block) +
                                " tx=" + to_string(tx) + " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot +
                                " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                                " substate.oldStateRoot=" + txState.persistence[persistence].subState[currentSubState].oldStateRoot);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                            batchState.timeMetricStorage.add("flush UUID inconsistent old state roots", TimeDiff(t));
                            batchState.timeMetricStorage.print("State Manager calls");
#endif
                            Unlock();
                            return ZKR_STATE_MANAGER;
                        }
                        break;
                    }
                    uint64_t previousSubState = txState.persistence[persistence].subState[currentSubState].previousSubState;
                    if (txState.persistence[persistence].subState[previousSubState].newStateRoot == txState.persistence[persistence].subState[currentSubState].oldStateRoot)
                    {
                        currentSubState = previousSubState;
                        continue;
                    }

                    // Search for the previous state
                    uint64_t i=0;
                    for (; i<currentSubState; i++)
                    {
                        if (txState.persistence[persistence].subState[i].newStateRoot == txState.persistence[persistence].subState[currentSubState].oldStateRoot)
                        {
                            previousSubState = i;
                            break;
                        }
                    }
                    if (i == currentSubState)
                    {
                        // If the origin of this sub-state is the tx old state root, then we are done
                        if (txState.persistence[persistence].subState[currentSubState].oldStateRoot == txState.persistence[persistence].oldStateRoot)
                        {
                            break;
                        }

                        // Otherwise, we could not find a sub-state that connects to this one
                        zklog.error("StateManager::flush() could not find previous tx sub-state: batchUUID=" + batchUUID +
                            " newStateRoot=" + _newStateRoot +
                            " block=" + to_string(block) +
                            " tx=" + to_string(tx) +
                            " txState.oldStateRoot=" + txState.persistence[persistence].oldStateRoot +
                            " currentSubState=" + to_string(txState.persistence[persistence].currentSubState) +
                            " substate.oldStateRoot=" + txState.persistence[persistence].subState[currentSubState].oldStateRoot);
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                        batchState.timeMetricStorage.add("flush UUID cannot find previous tx sub-state", TimeDiff(t));
                        batchState.timeMetricStorage.print("State Manager calls");
#endif
                        Unlock();
                        return ZKR_STATE_MANAGER;
                    }
                    currentSubState = previousSubState;
                }
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("find valid substates", TimeDiff(t2));
#endif

                /////////////////////////////////
                // Load data to write database //
                /////////////////////////////////

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                gettimeofday(&t2, NULL);
#endif

                // For all sub-states
                for (uint64_t ss = 0; ss < txState.persistence[persistence].subState.size(); ss++)
                {
                    // Skip invalid sub-states (if purge is active)
                    if (db.config.stateManagerPurge &&
                        ( !txState.persistence[persistence].subState[ss].bValid ||
                          (txState.persistence[persistence].subState[ss].oldStateRoot == txState.persistence[persistence].subState[ss].newStateRoot) ) )
                    {
                        continue;
                    }

                    // Add node keys to dbWriteNodes
                    dbWriteNodes.insert( txState.persistence[persistence].subState[ss].dbWriteNodes.begin(),
                                         txState.persistence[persistence].subState[ss].dbWriteNodes.end());

                    // Delete node keys (if purge is active)
                    if (db.config.stateManagerPurge)
                    {
                        for (uint64_t k = 0; k < txState.persistence[persistence].subState[ss].dbDeleteNodes.size(); k++)
                        {
                            dbWriteNodes.erase(txState.persistence[persistence].subState[ss].dbDeleteNodes[k]);
                        }
                    }

                    // Copy new state root
                    lastNewStateRoot = txState.persistence[persistence].newStateRoot;
                }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("load data to write to DB", TimeDiff(t2));
#endif

                ///////////////////////////////////////////
                // Write programs of this TX to database //
                ///////////////////////////////////////////

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                gettimeofday(&t2, NULL);
#endif
                // For all programs in dbWritePrograms
                unordered_map<string, vector<uint8_t>>::const_iterator writeIt;
                for ( writeIt = txState.persistence[persistence].dbWritePrograms.begin();
                      writeIt != txState.persistence[persistence].dbWritePrograms.end();
                      writeIt++ )
                {
                    // Call db.setProgram
                    zkr = db.setProgram(writeIt->first, writeIt->second, persistence == PERSISTENCE_DATABASE ? 1 : 0);
                    if (zkr != ZKR_SUCCESS)
                    {
                        zklog.error("StateManager::flush() failed calling db.writeProgram() result=" + zkresult2string(zkr));
                        state.erase(it);

                        //TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                        batchState.timeMetricStorage.add("flush error db.writeProgram", TimeDiff(t));
                        batchState.timeMetricStorage.print("State Manager calls");
#endif
                        Unlock();
                        return zkr;
                    }
                }
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
                batchState.timeMetricStorage.add("db.setProgram", TimeDiff(t2));
#endif
            }
        }
    }

    // Write nodes to database
    unordered_map<string, vector<Goldilocks::Element>>::const_iterator writeIt;
    for (writeIt = dbWriteNodes.begin(); writeIt != dbWriteNodes.end(); writeIt++)
    {
        zkr = db.write(writeIt->first, NULL, writeIt->second, _persistence == PERSISTENCE_DATABASE ? 1 : 0);
        if (zkr != ZKR_SUCCESS)
        {
            zklog.error("StateManager::flush() failed calling db.write() result=" + zkresult2string(zkr));
            state.erase(it);

            //TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
            batchState.timeMetricStorage.add("flush error db.write", TimeDiff(t));
            batchState.timeMetricStorage.print("State Manager calls");
#endif
            Unlock();
            return zkr;
        }
    }

    // Write last new state root to database
    if (!lastNewStateRoot.empty())
    {
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        gettimeofday(&t2, NULL);
#endif
        // Convert string to field element array
        Goldilocks::Element newStateRootFea[4];
        string2fea(db.fr, lastNewStateRoot, newStateRootFea);

        // Call db.updateStateRoot()
        zkr = db.updateStateRoot(newStateRootFea);
        if (zkr != ZKR_SUCCESS)
        {
            zklog.error("StateManager::flush() failed calling db.updateStateRoot() result=" + zkresult2string(zkr));
            state.erase(it);

            //TimerStopAndLog(STATE_MANAGER_FLUSH);

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
            batchState.timeMetricStorage.add("flush error db.updateStateRoot", TimeDiff(t));
            batchState.timeMetricStorage.print("State Manager calls");
#endif
            Unlock();
            return zkr;
        }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
        batchState.timeMetricStorage.add("db.updateStateRoot", TimeDiff(t2));
#endif
    }

    // Flush written data to remote database

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    gettimeofday(&t2, NULL);
#endif
    zkr = db.flush(flushId, lastSentFlushId);
    if (zkr != ZKR_SUCCESS)
    {
        zklog.error("StateManager::flush() failed calling db.flush() result=" + zkresult2string(zkr));
    }

#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    batchState.timeMetricStorage.add("db.flush", TimeDiff(t2));
    batchState.timeMetricStorage.add("flush success", TimeDiff(t));
    batchState.timeMetricStorage.print("State Manager calls");
#endif
    
    // Delete this batch UUID state
    state.erase(it);

    Unlock();

    //TimerStopAndLog(STATE_MANAGER_FLUSH);

    return zkr;
}

zkresult StateManager::cancelBatch (const string &batchUUID)
{
#ifdef LOG_TIME_STATISTICS_STATE_MANAGER
    struct timeval t;
    gettimeofday(&t, NULL);
#endif

    TimerStart(STATE_MANAGER_CANCEL_BATCH);

#ifdef LOG_STATE_MANAGER
    zklog.info("StateManager::cancelBatch() batchUUID=" + batchUUID);
#endif

    Lock();

    // Find batch state for this uuid
    unordered_map<string, BatchState>::iterator it;
    it = state.find(batchUUID);
    if (it == state.end())
    {
        zklog.warning("StateManager::cancelBatch() found no batch state for batch UUID=" + batchUUID + "; normal if no SMT activity happened");
        TimerStopAndLog(STATE_MANAGER_CANCEL_BATCH);
        Unlock();
        return ZKR_STATE_MANAGER;
    }
    state.erase(it);

    Unlock();

    TimerStopAndLog(STATE_MANAGER_CANCEL_BATCH);

    return ZKR_SUCCESS;
}

void StateManager::print (bool bDbContent)
{
    uint64_t totalDbWrites[PERSISTENCE_SIZE] = {0, 0, 0};
    uint64_t totalDbDeletes[PERSISTENCE_SIZE] = {0, 0, 0};
    zklog.info("StateManager::print():");
    zklog.info("state.size=" + to_string(state.size()));
    unordered_map<string, BatchState>::const_iterator stateIt;
    uint64_t batchStateCounter = 0;
    for (stateIt = state.begin(); stateIt != state.end(); stateIt++)
    {
        const BatchState &batchState = stateIt->second;
        zklog.info("  batchState=" + to_string(batchStateCounter));
        batchStateCounter++;
        zklog.info("  BatchUUID=" + stateIt->first);
        zklog.info("  oldStateRoot=" + batchState.oldStateRoot);
        zklog.info("  currentStateRoot=" + batchState.currentStateRoot);
        zklog.info("  currentBlock=" + to_string(batchState.currentBlock));

        for (uint64_t block=0; block<batchState.blockState.size(); block++)
        {
            zklog.info("    BLOCK=" + to_string(block) + "/" + to_string(batchState.blockState.size()));
            const BlockState &blockState = batchState.blockState[block];

            zklog.info("    oldStateRoot=" + blockState.oldStateRoot);
            zklog.info("    currentStateRoot=" + blockState.currentStateRoot);
            zklog.info("    currentTx=" + to_string(blockState.currentTx));       

            for (uint64_t tx=0; tx<blockState.txState.size(); tx++)
            {
                zklog.info("      TX=" + to_string(tx) + "/" + to_string(blockState.txState.size()));
                const TxState &txState = blockState.txState[tx];

                for (uint64_t persistence = 0; persistence < PERSISTENCE_SIZE; persistence++)
                {
                    //if (persistence != PERSISTENCE_DATABASE) continue;
                    zklog.info("        persistence=" + to_string(persistence) + "=" + persistence2string((Persistence)persistence));
                    zklog.info("          oldStateRoot=" + txState.persistence[persistence].oldStateRoot);
                    zklog.info("          newStateRoot=" + txState.persistence[persistence].newStateRoot);
                    zklog.info("          currentSubState=" + to_string(txState.persistence[persistence].currentSubState));
                    zklog.info("          txSubState.size=" + to_string(txState.persistence[persistence].subState.size()));
                    for (uint64_t i=0; i<txState.persistence[persistence].subState.size(); i++)
                    {
                        const TxSubState &txSubState = txState.persistence[persistence].subState[i];
                        zklog.info("            txSubState=" + to_string(i));
                        zklog.info("              oldStateRoot=" + txSubState.oldStateRoot);
                        zklog.info("              newStateRoot=" + txSubState.newStateRoot);
                        zklog.info("              valid=" + to_string(txSubState.bValid));
                        zklog.info("              previousSubState=" + to_string(txSubState.previousSubState));
                        zklog.info("              dbWriteNodes.size=" + to_string(txSubState.dbWriteNodes.size()));

                        totalDbWrites[persistence] += txSubState.dbWriteNodes.size();
                        if (bDbContent)
                        {
                            unordered_map<string, vector<Goldilocks::Element>>::const_iterator dbIt;
                            for (dbIt = txSubState.dbWriteNodes.begin(); dbIt != txSubState.dbWriteNodes.end(); dbIt++)
                            {
                                zklog.info("                " + dbIt->first);
                            }
                        }
                        zklog.info("              dbDeleteNodes.size=" + to_string(txSubState.dbDeleteNodes.size()));
                        totalDbDeletes[persistence] += txSubState.dbDeleteNodes.size();
                        if (bDbContent)
                        {
                            for (uint64_t j=0; j<txSubState.dbDeleteNodes.size(); j++)
                            {
                                zklog.info("                " + txSubState.dbDeleteNodes[j]);
                            }
                        }
                    }
                    zklog.info("          dbWritePrograms.size=" + to_string(txState.persistence[persistence].dbWritePrograms.size()));
                    if (bDbContent)
                    {
                        unordered_map<string, vector<uint8_t>>::const_iterator dbIt;
                        for (dbIt = txState.persistence[persistence].dbWritePrograms.begin(); dbIt != txState.persistence[persistence].dbWritePrograms.end(); dbIt++)
                        {
                            zklog.info("                " + dbIt->first);
                        }
                    }
                }
            }
        }
    }

    uint64_t totalWrites = 0;
    uint64_t totalDeletes = 0;
    for (uint64_t persistence=0; persistence<PERSISTENCE_SIZE; persistence++)
    {
        zklog.info("total db writes[" + persistence2string((Persistence)persistence) + "]=" + to_string(totalDbWrites[persistence]));
        totalWrites += totalDbWrites[persistence];
        zklog.info("total db deletes[" + persistence2string((Persistence)persistence) + "]=" + to_string(totalDbDeletes[persistence]));
        totalDeletes += totalDbDeletes[persistence];
    }
    zklog.info("total writes=" + to_string(totalWrites));
    zklog.info("total deletes=" + to_string(totalDeletes));
}