#include <algorithm>
#include <cmath>
#include <cstddef>
#include <print>

double max_gradient(const double *start, std::size_t size) {
  if (size < 2)
    return 0.0;

  double max_dist= 0.0;

  const double *end= start + size - 1;
#pragma omp simd reduction(max : max_dist)
  for (const double *ptr= start; ptr < end; ++ptr) {
    double val_curr= *ptr;
    double val_next= *(ptr + 1);
    max_dist= std::max(max_dist, std::fabs(val_curr - val_next));
  }
  return max_dist;
}

int main() {
  double mesh_values[]= {0.0, 0.5, 2.0, 1.5, 3.0, 8.0, 8.5};
  std::size_t size= 7;
  double max_diff= max_gradient(mesh_values, size);
  std::println("this is the maximum distance: {}", max_diff);
  return 0;
}
