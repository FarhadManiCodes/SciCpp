#include <algorithm>  // for ranges::max
#include <cmath>      // for std::abs
#include <print>
#include <ranges>
#include <vector>

int main() {
  // 1. Setup Data
  std::vector<double> u_num= {1.001, 2.005, 3.002, 4.000};
  std::vector<double> u_exact= {1.000, 2.000, 3.000, 4.000};

  // 2. Define the Math Kernel (The Lambda)
  // Notice: It takes two doubles, NOT a tuple!
  auto error_kernel= [](double u, double u_true) { return std::abs(u - u_true); };

  // 3. Create the Pipeline (Lazy)
  // No math happens here yet. No memory is allocated.
  auto error_view= std::views::zip_transform(error_kernel, u_num, u_exact);

  // 4. Execute (Reduction)
  // The pipeline pulls values one by one to find the max.
  double max_error= std::ranges::max(error_view);

  std::println("Max Error L_inf: {}", max_error);
}
