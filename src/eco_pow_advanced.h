#ifndef ECO_POW_ADVANCED_H
#define ECO_POW_ADVANCED_H

#include <string>
#include <cstdint>

struct EcoPowResultAdvanced {
    uint64_t nonce;
    std::string hash;
    std::string zkProof; // Simulated Zero‑Knowledge Proof
    double elapsed;      // Elapsed time in seconds
};

EcoPowResultAdvanced eco_pow_advanced(const std::string &block_data, int baseDifficulty);

#endif // ECO_POW_ADVANCED_H
