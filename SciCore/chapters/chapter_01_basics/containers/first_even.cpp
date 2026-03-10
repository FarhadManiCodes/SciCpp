#include <algorithm>
#include <print>  // C++23
#include <vector>

bool isEven(int n) {
  return n % 2 == 0;
}

int main() {
  std::vector<int> co= {2019, 2020, 2021, 2022, 2023, 2024};

  // Using std::ranges::find_if
  auto it= std::ranges::find_if(co, isEven);

  if (it != co.end()) {
    std::println("First even number: {}", *it);
  } else {
    std::println("No even number found.");
  }

  return 0;
}
