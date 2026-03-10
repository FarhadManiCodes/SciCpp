// ==========================================
// FILE: stress_modern.cpp
// COMPILE: g++ -O3 -std=c++23 stress_modern.cpp -o modern
// (If C++23 is not available, use -std=c++17 and swap println for cout)
// ==========================================
#include <print>           // C++23
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

int main() {
    const int N_PARTICLES = 2000000; 
    const int N_TYPES = 10000;       

    std::println("Generating 2M particles (Modern)...");
    std::vector<std::string> data;
    data.reserve(N_PARTICLES);
    for(int i = 0; i < N_PARTICLES; ++i) {
        data.push_back("particle_signature_detector_A_" + std::to_string(i % N_TYPES));
    }

    auto start = std::chrono::high_resolution_clock::now();

    // 1. Use Hash Map
    std::unordered_map<std::string, int> particle_counts;
    
    // 2. CRITICAL OPTIMIZATION: Reserve bucket count
    // Prevents "Rehashing" (moving data around) as the map grows.
    particle_counts.reserve(N_TYPES); 

    for(const auto& s : data) {
        // 3. MODERN OPTIMIZATION: try_emplace
        // Look up 's'. 
        // If found: Do NOTHING. No allocation. No copying.
        // If not found: Only then create the entry.
        auto [iter, success] = particle_counts.try_emplace(s, 0);
        
        // Update count
        iter->second++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::println("Modern Time: {} seconds.", elapsed.count());
    std::println("Map Size: {}", particle_counts.size());

    return 0;
}
