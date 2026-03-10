#include <algorithm>
#include <cmath>
#include <cstddef>
#include <format>
#include <print>
#include <span>
#include <stdexcept>
#include <string>

void normalize(double* start, std::size_t size) {
  if (size < 1) return;
  const double* end= start + size;
  double max_vlaue= 0.0;
  for (const double* ptr= start; ptr < end; ++ptr) {
    max_vlaue= std::max(max_vlaue, std::fabs(*ptr));
  }
  if (max_vlaue < 1e-10) {
    std::string error_msg=
        std::format("max value {} is too close to 0", max_vlaue);
    throw std::runtime_error(error_msg);
  }
  double inv_max= 1.0 / max_vlaue;
#pragma omp simd
  for (double* ptr= start; ptr < end; ++ptr) {
    *ptr= *ptr * inv_max;
  }
}

int main() {
  double mesh_values[]= {0.0, 0.5, 2.0, 1.5, 3.0, 8.0, 8.5};
  std::size_t size= 7;
  normalize(mesh_values, size);
  std::println("the normalize array is: {:n:.5f}",
               std::span(mesh_values, size));
  return 0;
}
