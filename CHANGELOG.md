# Changelog

All notable changes to this project will be documented in this file.

## [Prototype]

### Dynamic Difficulty Adjustment
- **Real-Time Data Integration:**  
  - Integrated libcurl-based HTTP API calls to fetch real-time data (e.g., electricity prices, network load).
  - Computed a `RealTimeFactor` from the API response, which dynamically scales the base difficulty.
  - Added logging to display the retrieved real-time factor and the adjusted difficulty.

### Enhanced Cryptographic Security (Simulated Zero-Knowledge Proof)
- **Simulated ZK Proof Generation:**  
  - Implemented a function that generates a simulated Zero-Knowledge Proof by hashing the block data, the discovered nonce, and a secret salt.
  - This function serves as a placeholder for a future integration with a proper ZK proof framework (e.g., libsnark or ZoKrates).

### Hardware Optimizations & Parallelization
- **OpenMP Parallelization:**  
  - Integrated OpenMP to parallelize the nonce search across multiple CPU cores.
  - Each thread starts at a different nonce and increments by the total number of threads, ensuring a balanced search.
- **Hardware-Specific Delays:**  
  - Added conditional delays using compiler macros to insert longer pauses on ARM architectures, reducing energy consumption on low-power devices.
- **Adaptive Energy Efficiency:**  
  - Optimized inner loops to periodically log progress (every 100,000 nonces) for performance monitoring.
  - Implemented high-resolution timers to accurately measure and log computation time.

### Robust Logging & Error Handling
- **Detailed Logging:**  
  - Used OpenSSL and libcurl error handling to log detailed error messages.
  - Logging is integrated at key operations: fetching real-time data, computing hashes, generating simulated ZK proofs, and during the parallel nonce search.
- **Structured Console Output:**  
  - Provided periodic status updates (e.g., current nonce, partial hash values, adjusted difficulty) to monitor the mining process.

### Code Structure and Modularity
- **Modular Design:**  
  - Separated core functionality into header (`eco_pow_advanced.h`) and source files (`eco_pow_advanced.cpp`, `main.cpp`).
  - Implemented helper functions for:
    - SHA‑256 hash computation (using OpenSSL)
    - Real-time factor fetching via libcurl
    - Hardware-specific delay determination
    - Simulated Zero‑Knowledge Proof generation
- **CMake Build System:**  
  - Configured CMake to locate and link OpenSSL, libcurl, and OpenMP libraries.
  - Ensured the project builds across multiple platforms with a consistent build process.

### Performance & Energy Efficiency
- **Adaptive Nonce Search:**  
  - Dynamically adjusts the nonce search based on the real-time factor, effectively adapting the energy consumption to current conditions.
- **Energy-Efficient Loops:**  
  - The mining loop incorporates delays based on hardware type to reduce unnecessary power draw.
- **Accurate Time Measurement:**  
  - Utilizes high-resolution timers to measure the total computation time, logging the elapsed time once a valid nonce is found.

## [Initial Release] - 2025-02-13
### Added
- Initial release of the ECO‑PoW proof-of-concept.
- Basic dynamic difficulty adjustment using simulated real-time factors.
- Simulated Zero‑Knowledge Proof generation function.
- Parallelized nonce search using OpenMP with hardware-specific delay optimizations.
- Comprehensive logging and error handling mechanisms.
- Modular code structure with separate header and source files.
- CMake build configuration supporting OpenSSL, libcurl, and OpenMP.
- Detailed README and LICENSE files.

### Changed
- N/A

### Fixed
- N/A
