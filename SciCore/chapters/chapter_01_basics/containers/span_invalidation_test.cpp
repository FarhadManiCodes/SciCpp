#include <print>  // C++23: The new standard for I/O
#include <span>
#include <string_view>
#include <vector>

// Helper to print memory addresses clearly
void print_status(std::string_view label, const std::vector<int>& v, std::span<int> s) {
  std::println("--- {} ---", label);

  // {:p} is the format specifier for pointers (hex address)
  std::println("Vector Data Address: {:p} (Size: {}, Cap: {})", static_cast<const void*>(v.data()),
               v.size(), v.capacity());

  std::println("Span   Data Address: {:p}", static_cast<void*>(s.data()));

  if (s.data() == v.data()) {
    std::println("STATUS: [SAFE] Span and Vector match.\n");
  } else {
    std::println("STATUS: [CRITICAL FAILURE] Span points to OLD memory!\n");
  }
}

void run_unsafe_experiment() {
  std::println("========================================");
  std::println("EXPERIMENT 1: Unsafe (No Reserve)");
  std::println("========================================");

  std::vector<int> vec= {1, 2};
  std::span<int> view= vec;

  print_status("Initial State", vec, view);

  std::println(">> Pushing back elements to force reallocation...\n");
  for (int i= 0; i < 10; ++i) {
    vec.push_back(i + 10);
  }

  print_status("After Push Back", vec, view);

  std::println(">> Attempting to read via Span...");
  // Note: This is Undefined Behavior, but we print it to prove the point.
  std::println("   Span[0] value: {} (Likely Garbage!)", view[0]);
  std::println("========================================\n");
}

void run_safe_experiment() {
  std::println("========================================");
  std::println("EXPERIMENT 2: Safe (With Reserve)");
  std::println("========================================");

  std::vector<int> vec= {1, 2};

  std::println(">> Reserving memory for 20 elements...");
  vec.reserve(20);

  // Create span AFTER reserve
  std::span<int> view= vec;

  print_status("Initial State", vec, view);

  std::println(">> Pushing back elements...\n");
  for (int i= 0; i < 10; ++i) {
    vec.push_back(i + 10);
  }

  print_status("After Push Back", vec, view);

  std::println(">> Reading via Span:");
  std::println("   Span[0] value: {} (Correct)", view[0]);
}

int main() {
  run_unsafe_experiment();
  run_safe_experiment();
  return 0;
}
