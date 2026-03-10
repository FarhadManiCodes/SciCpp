// ==========================================
// FILE: stress_legacy.cpp
// COMPILE: g++ -O3 -std=c++17 stress_legacy.cpp -o legacy
// ==========================================
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>

int main() {
    const int N_PARTICLES = 2000000; 
    const int N_TYPES = 10000;       

    // 1. Generate Data (Deterministic)
    // We use LONG strings to defeat Small String Optimization (SSO)
    // ensuring memory allocation happens, which exposes the flaw in 'insert'.
    std::cout << "Generating 2M particles (Legacy)..." << std::endl;
    std::vector<std::string> data;
    data.reserve(N_PARTICLES);
    for(int i = 0; i < N_PARTICLES; ++i) {
        // A string longer than 22 chars to force Heap allocation
        data.push_back("particle_signature_detector_A_" + std::to_string(i % N_TYPES));
    }

    // 2. Start Timer
    auto start = std::chrono::high_resolution_clock::now();

    // 3. The Bottleneck
    std::map<std::string, int> particle_counts;

    for(const auto& s : data) {
        // LEGACY FLAW: 
        // This constructs a std::pair<string, int>.
        // To do that, it COPIES 's' into the pair.
        // If the key exists, it destroys the pair. 
        // That is 2 million useless heap allocations/deallocations.
        auto res = particle_counts.insert({s, 0});
        
        // Update count
        res.first->second++;
    }

    // 4. Stop Timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Legacy Time: " << elapsed.count() << " seconds." << std::endl;
    std::cout << "Map Size: " << particle_counts.size() << std::endl;

    return 0;
}
