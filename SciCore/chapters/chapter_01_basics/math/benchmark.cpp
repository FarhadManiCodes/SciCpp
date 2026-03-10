#include <boost/math/tools/roots.hpp>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <expected>
#include <numeric>
#include <print>
#include <utility>

// =========================================================
// 1. YOUR IMPLEMENTATION (Namespace "Mine")
// =========================================================
namespace Mine {

enum class SolverError { MaxIterationsReached, BracketInvalid };

struct RootResult {
    double root;
    double f_value;
    std::size_t iterations;
};

// Concept to ensure Func is callable with double
template <typename Func>
concept UnaryRealFunction = requires(Func f, double x) {
    { f(x) } -> std::convertible_to<double>;
};

template <UnaryRealFunction Func>
std::expected<RootResult, SolverError> find_root_bisection(
    Func f, double min, double max, double tol = 1e-12, std::size_t max_iter = 100) {
    
    // Evaluate at boundaries
    double f_min = f(min);
    double f_max = f(max);

    // Exact hit checks
    if (std::abs(f_min) < tol) return RootResult{min, f_min, 0};
    if (std::abs(f_max) < tol) return RootResult{max, f_max, 0};

    // Safety: Verify we have a valid bracket (signs must differ)
    bool sign_min = std::signbit(f_min);
    [[unlikely]] if (sign_min == std::signbit(f_max)) {
        return std::unexpected(SolverError::BracketInvalid);
    }

    for (std::size_t i = 0; i < max_iter; ++i) {
        // C++20 midpoint (overflow safe)
        double mid = std::midpoint(min, max);
        double f_mid = f(mid);

        // Hybrid Termination:
        // 1. Residual is small: |f(x)| < tol
        // 2. Interval is small: |b-a| < tol (scaled)
        double scale = std::max(std::abs(min), std::abs(max));
        double interval_tol = tol * (1.0 + scale);

        if (std::abs(f_mid) < tol || (max - min) < interval_tol) {
            return RootResult{mid, f_mid, i + 1};
        }

        // Update bracket
        if (std::signbit(f_mid) == sign_min) {
            min = mid;
            sign_min = std::signbit(f_mid);
        } else {
            max = mid;
        }
    }
    return std::unexpected(SolverError::MaxIterationsReached);
}

} // namespace Mine

// =========================================================
// 2. BENCHMARK HARNESS
// =========================================================
int main() {
    auto f_n = [](double x) { return std::sin(5 * x) + std::cos(x); };
    
    // Setup
    double min = 0.0, max = 1.0;
    double tol = 1e-12;
    constexpr int N_WARMUP = 1'000;
    constexpr int N_RUNS   = 100'000;

    std::println("Benchmarking: sin(5x) + cos(x) on [0, 1]");
    std::println("Runs: {}", N_RUNS);
    std::println("-------------------------------------------------------------");

    // ---------------------------------------------------------
    // WARM-UP PHASE
    // ---------------------------------------------------------
    // This wakes up the CPU, fills the cache, and triggers branch predictors.
    std::print("Warming up... ");
    volatile double sink = 0.0; // Volatile prevents compiler from optimizing away the loop
    for(int i = 0; i < N_WARMUP; ++i) {
        auto r = Mine::find_root_bisection(f_n, min, max, tol);
        sink += r->root;
    }
    std::println("Done.");

    // ---------------------------------------------------------
    // BENCHMARK 1: YOURS
    // ---------------------------------------------------------
    auto start_mine = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < N_RUNS; ++i) {
        auto res = Mine::find_root_bisection(f_n, min, max, tol);
        sink += res->root; // Force dependency
    }
    
    auto end_mine = std::chrono::high_resolution_clock::now();
    auto dur_mine = std::chrono::duration_cast<std::chrono::nanoseconds>(end_mine - start_mine).count();

    // ---------------------------------------------------------
    // BENCHMARK 2: BOOST
    // ---------------------------------------------------------
    // Boost requires a termination functor
    auto boost_tol_func = [tol](double a, double b) {
        double scale = std::max(std::abs(a), std::abs(b));
        return std::abs(a - b) < tol * (1.0 + scale);
    };

    std::uintmax_t boost_iters = 100;
    
    auto start_boost = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < N_RUNS; ++i) {
        boost_iters = 100; // Reset iter counter every time
        auto range = boost::math::tools::bisect(f_n, min, max, boost_tol_func, boost_iters);
        sink += range.first; // Force dependency
    }
    
    auto end_boost = std::chrono::high_resolution_clock::now();
    auto dur_boost = std::chrono::duration_cast<std::chrono::nanoseconds>(end_boost - start_boost).count();

    // ---------------------------------------------------------
    // REPORT
    // ---------------------------------------------------------
    double avg_mine  = (double)dur_mine / N_RUNS;
    double avg_boost = (double)dur_boost / N_RUNS;
    
    std::println("{:<10} | {:<10} ns/call", "Solver", "Avg Time");
    std::println("---------------------------------");
    std::println("{:<10} | {:.2f}", "Mine", avg_mine);
    std::println("{:<10} | {:.2f}", "Boost", avg_boost);
    std::println("---------------------------------");
    std::println("Ratio (Mine/Boost): {:.2f}x", avg_mine / avg_boost);
    
    // Sanity check to ensure sink wasn't optimized out (prints garbage, but required)
    if(sink == 12345.6789) std::println("Magic happened"); 

    return 0;
}
