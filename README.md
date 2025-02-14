# ECO‑PoW Example

This repository provides a proof-of-concept implementation of an eco‑friendly Proof of Work (ECO‑PoW) algorithm in C++. ECO‑PoW dynamically adjusts its difficulty using simulated real‑time data (e.g., electricity prices or network load) and enhances security with a simulated zero‑knowledge proof. The nonce search is parallelized with OpenMP and incorporates hardware‑specific optimizations to reduce energy consumption.

**Note:** This project is only an example and is not production‑ready.

## Features

- **Dynamic Difficulty Adjustment:**  
  The algorithm fetches a real‑time factor via libcurl and scales the base difficulty accordingly.

- **Enhanced Cryptographic Security:**  
  A simulated zero‑knowledge proof is generated (using an extra SHA‑256 hash with a secret salt) to provide additional cryptographic assurance. For production, integrate a proper ZK‑Proof framework (e.g., libsnark or ZoKrates).

- **Hardware Optimizations & Parallelization:**  
  Uses OpenMP to parallelize the nonce search and applies platform-specific delays (e.g., longer delays on ARM processors) to minimize energy consumption.

- **Robust Logging & Error Handling:**  
  Detailed logging outputs progress (e.g., current nonce attempts, partial hash values, adjusted difficulty) and errors to help with debugging and performance monitoring.

## Repository Structure

eco-pow 
├── CMakeLists.txt 
├── README.md 
├── CHANGELOG.md 
├── LICENSE 
└── src/ 
├── eco_pow_advanced.h 
├── eco_pow_advanced.cpp 
└── main.cpp


## Build and Run

### Prerequisites
- C++ compiler (supporting C++11 or higher)
- CMake (version 3.10 or higher)
- OpenSSL development libraries
- libcurl development libraries
- OpenMP support (usually included in modern compilers)

### Build Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/MrMiner-org/ECO-POW
   cd eco-pow-cpp
   ```
   
2. Create a build directory and run CMake:
	```bash
	mkdir build && cd build
	cmake ..
	make
	```
	
### Run

	```bash
./eco_pow_cpp
```

### Sample Output
Starting advanced ECO‑PoW computation... Current RealTimeFactor: 1.23 Adjusted difficulty: 4 Tried nonce: 100000, current hash: 0000ab1234... Nonce found: 1234567 Hash: 0000f1a2b3c4d5e6f7... Zero‑Knowledge Proof (simulated): a1b2c3d4e5f6... Time taken: 45.67 seconds

	```bash
Starting advanced ECO‑PoW computation...
Current RealTimeFactor: 1.23
Adjusted difficulty: 4
Tried nonce: 100000, current hash: 0000ab1234...
Nonce found: 1234567
Hash: 0000f1a2b3c4d5e6f7...
Zero‑Knowledge Proof (simulated): a1b2c3d4e5f6...
Time taken: 45.67 seconds
```


## Changelog

Please refer to [CHANGELOG.md](CHANGELOG.md) for detailed changes and improvements.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

