#include "eco_pow_advanced.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <curl/curl.h>
#ifdef _OPENMP
#include <omp.h>
#include <atomic>
#endif

// Helper function to compute SHA‑256 hash of a string
std::string sha256(const std::string &data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Callback for libcurl to store response in a string
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fetch real‑time factor (e.g., electricity price or network load) via HTTP API
double getRealTimeFactor() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    double factor = 1.0; // Default factor

    curl = curl_easy_init();
    if(curl) {
        // Replace with a real API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/realtime_factor");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        } else {
            try {
                factor = std::stod(readBuffer);
            } catch (...) {
                std::cerr << "Error parsing real‑time data. Using default factor 1.0.\n";
            }
        }
        curl_easy_cleanup(curl);
    }
    std::cout << "Current RealTimeFactor: " << factor << "\n";
    return factor;
}

// Hardware optimization: Return a delay in milliseconds based on hardware architecture
int getHardwareOptimizationDelay() {
#if defined(__arm__) || defined(__aarch64__)
    return 10; // For ARM platforms, use 10 ms delay
#else
    return 5;  // For other platforms, use 5 ms delay
#endif
}

// Simulate generating a Zero‑Knowledge Proof using a secret salt.
// In production, replace with a real ZK‑proof generation using a framework like libsnark or ZoKrates.
std::string generateZKProofReal(const std::string &block_data, uint64_t nonce) {
    std::string secret = "real_secret_salt";
    std::string input = block_data + std::to_string(nonce) + secret;
    return sha256(input);
}

EcoPowResultAdvanced eco_pow_advanced(const std::string &block_data, int baseDifficulty) {
    EcoPowResultAdvanced result;
    uint64_t finalNonce = 0;
    std::string finalHash;
#ifdef _OPENMP
    std::atomic<bool> found(false);
    int num_threads = omp_get_max_threads();
#else
    bool found = false;
#endif

    // Dynamic difficulty adjustment using real‑time factor
    double realTimeFactor = getRealTimeFactor();
    int adjustedDifficulty = static_cast<int>(baseDifficulty * realTimeFactor);
    if (adjustedDifficulty < 1) adjustedDifficulty = 1;
    std::string prefix(adjustedDifficulty, '0');
    std::cout << "Adjusted difficulty: " << adjustedDifficulty << "\n";

    auto start = std::chrono::steady_clock::now();

#ifdef _OPENMP
    #pragma omp parallel
    {
        uint64_t local_nonce = omp_get_thread_num();
        while (!found.load()) {
            std::string input = block_data + std::to_string(local_nonce);
            std::string hash_result = sha256(input);

            // Insert hardware-specific delay to reduce power consumption
            std::this_thread::sleep_for(std::chrono::milliseconds(getHardwareOptimizationDelay()));

            if (hash_result.substr(0, adjustedDifficulty) == prefix) {
                if (!found.exchange(true)) {
                    finalNonce = local_nonce;
                    finalHash = hash_result;
                }
                break;
            }
            if (local_nonce % 100000 == 0 && local_nonce > 0) {
                #pragma omp critical
                {
                    std::cout << "Thread " << omp_get_thread_num() 
                              << " tried nonce: " << local_nonce 
                              << ", current hash: " << hash_result.substr(0, 10)
                              << "...\n";
                }
            }
            local_nonce += omp_get_num_threads();
        }
    }
#else
    // Sequential fallback if OpenMP is not available
    uint64_t nonce = 0;
    while (true) {
        std::string input = block_data + std::to_string(nonce);
        std::string hash_result = sha256(input);
        std::this_thread::sleep_for(std::chrono::milliseconds(getHardwareOptimizationDelay()));
        if (hash_result.substr(0, adjustedDifficulty) == prefix) {
            finalNonce = nonce;
            finalHash = hash_result;
            break;
        }
        if (nonce % 100000 == 0 && nonce > 0) {
            std::cout << "Tried nonce: " << nonce 
                      << ", current hash: " << hash_result.substr(0, 10)
                      << "...\n";
        }
        nonce++;
    }
#endif

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    result.nonce = finalNonce;
    result.hash = finalHash;
    result.zkProof = generateZKProofReal(block_data, finalNonce);
    result.elapsed = elapsed.count();
    return result;
}
