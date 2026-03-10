#include <boost/math/tools/roots.hpp>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <expected>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <print>
#include <string>
#include <vector>

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

template <typename Func>
concept UnaryRealFunction = requires(Func f, double x) {
    { f(x) } -> std::convertible_to<double>;
};

template <UnaryRealFunction Func>
std::expected<RootResult, SolverError> find_root_bisection(
    Func f, double min, double max, double tol = 1e-12, std::size_t max_iter = 100) {
    
    double f_min = f(min);
    double f_max = f(max);

    if (std::abs(f_min) < tol) return RootResult{min, f_min, 0};
    if (std::abs(f_max) < tol) return RootResult{max, f_max, 0};

    // SAFETY CHECK: This is what we are testing!
    bool sign_min = std::signbit(f_min);
    [[unlikely]] if (sign_min == std::signbit(f_max)) {
        return std::unexpected(SolverError::BracketInvalid);
    }

    for (std::size_t i = 0; i < max_iter; ++i) {
        // OVERFLOW PROTECTION: std::midpoint
        double mid = std::midpoint(min, max);
        double f_mid = f(mid);

        double scale = std::max(std::abs(min), std::abs(max));
        double interval_tol = tol * (1.0 + scale);

        if (std::abs(f_mid) < tol || (max - min) < interval_tol) {
            return RootResult{mid, f_mid, i + 1};
        }

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
// 2. TEST INFRASTRUCTURE
// =========================================================

struct TestCase {
    std::string name;
    double min;
    double max;
    double (*func)(double); // Function pointer wrapper
};

// Functions for the test cases
double f_invalid(double x) { return x * x + 1.0; } // Always positive
double f_pole(double x)    { return std::tan(x); } // Pole at pi/2 (~1.57)
double f_huge(double x)    { return x - 1e300; }   // Root at 1e300
double f_tiny(double x)    { return x; }           // Root at 0

int main() {
    std::vector<TestCase> cases = {
        // CASE 1: Invalid Bracket (Should Fail)
        {"Invalid Bracket (x^2 + 1)", 0.0, 10.0, f_invalid},

        // CASE 2: Singularity (Discontinuity mimics a root)
        // tan(x) goes +inf -> -inf at pi/2. Signs differ, but no root!
        {"Singularity (tan(x) at pi/2)", 1.5, 1.6, f_pole},

        // CASE 3: Massive Numbers (Overflow Risk)
        // Range is near max double. (min+max)/2 would be Infinity.
        {"Titan Numbers (1e300)", 0.9e300, 1.1e300, f_huge},

        // CASE 4: Subnormal Numbers (Underflow Risk)
        // Signs differ, but values are effectively 0 if squared.
        {"Quantum Numbers (1e-320)", -1e-320, 1e-320, f_tiny}
    };

    std::cout << std::fixed << std::setprecision(4);

    for (const auto& test : cases) {
        std::println("\n==========================================");
        std::println("TEST: {} on [{:.2g}, {:.2g}]", test.name, test.min, test.max);
        
        // --- RUN MINE ---
        std::print("[Mine]  Result: ");
        auto res = Mine::find_root_bisection(test.func, test.min, test.max);
        if (res) {
            std::println("Converged to {:.5g}", res->root);
        } else {
            // We expect this for invalid brackets!
            std::string err = (res.error() == Mine::SolverError::BracketInvalid) ? "BracketInvalid" : "MaxIter";
            std::println("FAILED GRACEFULLY (Error: {})", err);
        }

        // --- RUN BOOST ---
        std::print("[Boost] Result: ");
        try {
            // Boost Termination Condition
            auto tol = [](double a, double b) { return std::abs(a-b) < 1e-9; };
            std::uintmax_t iters = 100;
            
            // Boost typically THROWS or ASSERTS on bad brackets
            auto range = boost::math::tools::bisect(test.func, test.min, test.max, tol, iters);
            std::println("Converged to {:.5g}", (range.first + range.second)/2.0);
        
        } catch (const std::exception& e) {
            std::println("CRASHED/THREW: {}", e.what());
        }
    }
    return 0;
}
