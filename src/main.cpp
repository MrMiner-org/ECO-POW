#include "eco_pow_advanced.h"
#include <iostream>
#include <ctime>

int main() {
    // Generate block data based on the current time
    std::time_t now = std::time(nullptr);
    std::string block_data = "EcoBlock-Data-" + std::to_string(now);
    int baseDifficulty = 4;  // Base difficulty intended to replace all traditional PoW schemes

    std::cout << "Starting advanced ECO‑PoW computation...\n";
    
    EcoPowResultAdvanced result = eco_pow_advanced(block_data, baseDifficulty);
    
    std::cout << "Nonce found: " << result.nonce << "\n";
    std::cout << "Hash: " << result.hash << "\n";
    std::cout << "Zero‑Knowledge Proof (simulated): " << result.zkProof << "\n";
    std::cout << "Time taken: " << result.elapsed << " seconds\n";
    
    return 0;
}
