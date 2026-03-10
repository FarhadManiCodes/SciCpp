#include <chrono>
#include <cstddef>
#include <iostream>

#include "Matrix.hpp"  // Look how clean this is!

template <typename Func>
double measure_time(Func&& func) {
  auto start= std::chrono::high_resolution_clock::now();
  func();
  auto end= std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

void run_benchmark(size_t N) {
  std::cout << "Benchmarking Matrix Class (N=" << N << ")..." << std::endl;

  // 1. Create Objects (Memory is managed automatically!)
  Matrix A(N, N);
  Matrix B(N, N);
  Matrix C(N, N);

  // Initialize (Using the safe operator for setup)
  for (size_t i= 0; i < N; ++i) {
    for (size_t j= 0; j < N; ++j) {
      A(i, j)= 1.0;
      B(i, j)= 2.0;
    }
  }

  // 2. Get High-Performance Views
  // We grab the 'mdspan' handles before the loop to skip the bound checks
  auto A_view= A.view();
  auto B_view= B.view();
  auto C_view= C.view();

  // 3. Run the "Fast" Loop (i-k-j)
  double time= measure_time([&]() {
    for (size_t i= 0; i < N; ++i) {
      for (size_t k= 0; k < N; ++k) {
        double a_val= A_view[i, k];  // Fast C++23 access
        for (size_t j= 0; j < N; ++j) {
          C_view[i, j]+= a_val * B_view[k, j];
        }
      }
    }
  });

  std::cout << "Time: " << time << " s" << std::endl;
}

int main() {
  run_benchmark(1000);
  return 0;
}
