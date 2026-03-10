#include <cmath>
#include <concepts>
#include <cstddef>
#include <expected>
#include <functional>
#include <numeric>
#include <optional>
#include <print>
#include <string>
#include <utility>
#include <vector>

enum class SolverError { MaxIterationsReached, BracketInvalid };

struct RootResult {
  double root;
  double f_value;
  std::size_t iterations;
};

struct SolverConfig {
  double tol_x = 1e-12;       // Interval tolerance (MANDATORY for convergence)
  double tol_f = 1e-12;       // Residual tolerance (OPTIONAL optimization)
  std::size_t max_iter = 100;
};

template <typename Func>
concept UnaryRealFunction = requires(Func f, double x) {
  { f(x) } -> std::convertible_to<double>;
};

template <UnaryRealFunction Func>
std::expected<RootResult, SolverError> find_root_bisection(
    Func f, double min, double max, SolverConfig config = {}) {
  
  // Evaluate at boundaries
  double f_min = f(min);
  double f_max = f(max);
  
  // Check if root is exactly at a boundary
  [[unlikely]] if (std::abs(f_min) < config.tol_f)
    return RootResult{min, f_min, 0};
  [[unlikely]] if (std::abs(f_max) < config.tol_f)
    return RootResult{max, f_max, 0};
  
  // Verify we have a valid bracket (opposite signs)
  bool sign_min = std::signbit(f_min);
  [[unlikely]] if (sign_min == std::signbit(f_max)) {
    return std::unexpected(SolverError::BracketInvalid);
  }
  
  // Compute function scale for relative residual checking
  double f_scale = std::max(std::abs(f_min), std::abs(f_max));
  
  for (std::size_t i = 0; i < config.max_iter; ++i) {
    double mid = std::midpoint(min, max);
    double f_mid = f(mid);
    
    // 1. MANDATORY: Interval width convergence (bisection's guarantee)
    double scale = std::max(std::abs(min), std::abs(max));
    double interval_tol = config.tol_x * (1.0 + scale);
    
    if ((max - min) < interval_tol) {
      return RootResult{mid, f_mid, i + 1};
    }
    
    // 2. OPTIONAL: Residual check (optimization for well-behaved functions)
    if (config.tol_f > 0.0) {
      // Use BOTH absolute AND relative residual checks
      // Absolute: handles functions with small scale
      // Relative: handles functions with large scale (cliff hangers)
      double abs_residual = std::abs(f_mid);
      double rel_residual = abs_residual / f_scale;
      
      if (abs_residual < config.tol_f || rel_residual < config.tol_f) {
        return RootResult{mid, f_mid, i + 1};
      }
    }
    
    // Update bracket based on sign
    if (std::signbit(f_mid) == sign_min) {
      min = mid;
      sign_min = std::signbit(f_mid);
      // Update scale as bracket narrows
      f_scale = std::max(std::abs(f_mid), std::abs(f(max)));
    } else {
      max = mid;
      f_scale = std::max(std::abs(f(min)), std::abs(f_mid));
    }
  }
  
  return std::unexpected(SolverError::MaxIterationsReached);
}

struct TestCase {
  std::string name;
  double min;
  double max;
  std::function<double(double)> f;
  SolverConfig config = {};
  std::optional<double> exact_root = std::nullopt;
};

int main() {
  std::vector<TestCase> cases = {
    // Well-behaved function
    {"Well-Behaved sin/cos", 0.0, 1.0, 
     [](double x) { return std::sin(5 * x) + std::cos(x); }},
    
    // 1. The Flat-Liner
    // Root is exactly 1.0
    // Tests if you stop too early due to residual check.
    {"Flat-Liner (x-1)^9", 0.0, 2.0, 
     [](double x) { return std::pow(x - 1.0, 9); },
     {.tol_x = 1e-10, .tol_f = 0.0},
     1.0},  // Exact root
    
    // 2. The Cliff Hanger
    // Root is 43*ln(10)/100 (analytical solution)
    // Tests if you handle huge residuals gracefully.
    {"Cliff Hanger e^(100x)", 0.0, 1.0, 
     [](double x) { return std::exp(100.0 * x) - std::pow(10.0, 43.0); },
     {.tol_x = 1e-12, .tol_f = 1e-12},
     43.0 * std::log(10.0) / 100.0},  // Exact root
    
    // 3. Wien's Displacement Law
    // Root is approximately 4.965114231744...
    {"Wien's Law", 2.0, 10.0, 
     [](double x) { return 5.0 * (1.0 - std::exp(-x)) - x; }},
    
    // 4. Legendre Polynomial P5(x)
    // Root at 0 when bracketed at [-1, 1]
    {"Legendre P5 (multiple roots)", -1.0, 1.0, 
     [](double x) { 
       return 0.125 * (63*std::pow(x,5) - 70*std::pow(x,3) + 15*x); 
     },
     {},
     0.0},  // Exact root (when bracket contains 0)
  };
  
  std::println("╔════════════════════════════════════════════════════════════════╗");
  std::println("║          BISECTION METHOD - EDGE CASE TORTURE TEST             ║");
  std::println("╚════════════════════════════════════════════════════════════════╝\n");
  
  for (const auto& test : cases) {
    std::println("Test: {}", test.name);
    std::println("Bracket: [{}, {}]", test.min, test.max);
    std::println("Config: tol_x={:.0e}, tol_f={:.0e}, max_iter={}", 
                 test.config.tol_x, test.config.tol_f, test.config.max_iter);
    
    if (auto result = find_root_bisection(test.f, test.min, test.max, test.config)) {
      std::println("✓ Root found: {:.15f}", result->root);
      std::println("  f(root) = {:.6e}", result->f_value);
      std::println("  Iterations: {}", result->iterations);
      
      // Show exact root comparison if available
      if (test.exact_root) {
        double error = std::abs(result->root - *test.exact_root);
        std::println("  Exact root: {:.15f}", *test.exact_root);
        std::println("  Error: {:.6e}", error);
      }
      
      // Sanity check: verify it's actually close to a root
      if (std::abs(result->f_value) > 1e-6) {
        std::println("  ⚠️  Warning: Large absolute residual (function may be flat or steep)");
      }
    } else {
      switch (result.error()) {
        case SolverError::BracketInvalid:
          std::println("✗ Error: Invalid bracket (no sign change)");
          std::println("  f({}) = {:.6e}", test.min, test.f(test.min));
          std::println("  f({}) = {:.6e}", test.max, test.f(test.max));
          break;
        case SolverError::MaxIterationsReached:
          std::println("✗ Error: Maximum iterations reached");
          break;
      }
    }
    std::println("");
  }
  
  // Additional demonstration: Finding different roots of Legendre P5
  std::println("╔════════════════════════════════════════════════════════════════╗");
  std::println("║     FINDING MULTIPLE ROOTS OF LEGENDRE P5 BY BRACKETING        ║");
  std::println("╚════════════════════════════════════════════════════════════════╝\n");
  
  auto legendre_p5 = [](double x) { 
    return 0.125 * (63*std::pow(x,5) - 70*std::pow(x,3) + 15*x); 
  };
  
  // Exact roots of Legendre P5 (from mathematical tables)
  std::vector<std::tuple<double, double, double>> brackets_with_exact = {
    {-1.0, -0.8, -0.9061798459386640},   // Root near -0.906
    {-0.7, -0.3, -0.5384693101056831},   // Root near -0.538
    {-0.1, 0.1,   0.0},                  // Root at 0
    {0.3, 0.7,    0.5384693101056831},   // Root near 0.538
    {0.8, 1.0,    0.9061798459386640}    // Root near 0.906
  };
  
  for (const auto& [a, b, exact] : brackets_with_exact) {
    if (auto result = find_root_bisection(legendre_p5, a, b)) {
      double error = std::abs(result->root - exact);
      std::println("Bracket [{:+.1f}, {:+.1f}] → Root: {:+.16f}", a, b, result->root);
      std::println("                      Exact: {:+.16f}", exact);
      std::println("                      Error: {:.6e}\n", error);
    }
  }
  
  return 0;
}
