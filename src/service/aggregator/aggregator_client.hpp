#ifndef AGGREGATOR_CLIENT_HPP
#define AGGREGATOR_CLIENT_HPP

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "aggregator.grpc.pb.h"
#include "proof_fflonk.hpp"
#include "goldilocks_base_field.hpp"
#include "prover.hpp"

class AggregatorClient
{
public:
    Goldilocks &fr;
    const Config &config;
    Prover &prover;
    aggregator::v1::AggregatorService::Stub * stub;
    pthread_t t; // Client thread

public:
    AggregatorClient (Goldilocks &fr, const Config &config, Prover &prover);

    void runThread (void);
    void waitForThread (void);
    bool GetStatus (aggregator::v1::GetStatusResponse &getStatusResponse);
    bool GenBatchProof (const aggregator::v1::GenBatchProofRequest &genBatchProofRequest, aggregator::v1::GenBatchProofResponse &genBatchProofResponse);
    bool GenStatelessBatchProof (const aggregator::v1::GenStatelessBatchProofRequest &genStatelessBatchProofRequest, aggregator::v1::GenBatchProofResponse &genBatchProofResponse);
    bool GenAggregatedBatchProof (const aggregator::v1::GenAggregatedBatchProofRequest &genAggregatedBatchProofRequest, aggregator::v1::GenAggregatedBatchProofResponse &genAggregatedBatchProofResponse);
    bool GenBlobInnerProof (const aggregator::v1::GenBlobInnerProofRequest &genBlobInnerProofRequest, aggregator::v1::GenBlobInnerProofResponse &genBlobInnerProofResponse);
    bool GenBlobOuterProof (const aggregator::v1::GenBlobOuterProofRequest &genBlobOuterProofRequest, aggregator::v1::GenBlobOuterProofResponse &genBlobOuterProofResponse);
    bool GenAggregatedBlobOuterProof (const aggregator::v1::GenAggregatedBlobOuterProofRequest &genAggregatedBlowOuterRequest, aggregator::v1::GenAggregatedBlobOuterProofResponse &genAggregatedBlobOuterProofResponse);
    bool GenFinalProof (const aggregator::v1::GenFinalProofRequest &genFinalProofRequest, aggregator::v1::GenFinalProofResponse &genFinalProofResponse);
    bool Cancel (const aggregator::v1::CancelRequest &cancelRequest, aggregator::v1::CancelResponse &cancelResponse);
    bool GetProof (const aggregator::v1::GetProofRequest &getProofRequest, aggregator::v1::GetProofResponse &getProofResponse);
};

void* aggregatorClientThread(void* arg);

#endif