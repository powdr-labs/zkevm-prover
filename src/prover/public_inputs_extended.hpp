#ifndef PUBLIC_INPUTS_EXTENDED
#define PUBLIC_INPUTS_EXTENDED

#include <string>
#include <gmpxx.h>
#include "public_inputs.hpp"

using namespace std;

class PublicInputsExtended
{
public:
    PublicInputs publicInputs;

    string    inputHash;
    mpz_class newAccInputHash;
    uint32_t  newBatchNum;
    mpz_class newLocalExitRoot;
    mpz_class newStateRoot;

    // Fork 9 batch fields
    mpz_class currentL1InfoTreeRoot;
    uint32_t  currentL1InfoTreeIndex;

    // Blob inner fields
    mpz_class newBlobStateRoot;
    mpz_class newBlobAccInputHash;
    uint64_t  newBlobNum;
    mpz_class finalAccBatchHashData;
    mpz_class localExitRootFromBlob;
    bool      isInvalid;
    
    PublicInputsExtended() : newBatchNum(0), currentL1InfoTreeIndex(0), newBlobNum(0), isInvalid(false) {};

    bool operator==(PublicInputsExtended &publicInputsExtended)
    {
        return
            publicInputs     == publicInputsExtended.publicInputs &&
            inputHash        == publicInputsExtended.inputHash &&
            newAccInputHash  == publicInputsExtended.newAccInputHash &&
            newBatchNum      == publicInputsExtended.newBatchNum &&
            newLocalExitRoot == publicInputsExtended.newLocalExitRoot &&
            newStateRoot     == publicInputsExtended.newStateRoot;
    }
};

#endif