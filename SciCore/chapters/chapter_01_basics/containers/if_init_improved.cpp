#include <print>  // C++23 feature (Much faster than iostream)
#include <string>
#include <unordered_map>

int main() {
  // 1. Use unordered_map for O(1) lookup speed
  std::unordered_map<std::string, double> constants= {{"e", 2.7}, {"pi", 3.14}, {"h", 2}};

  // 2. The "If-Initializer" with Structured Binding
  // We use try_emplace instead of insert for efficiency.
  if (auto [iter, is_new]= constants.try_emplace("h", 6.6e-34); is_new) {
    // 3. Success Case: 'iter' points to the new entry
    std::println("Success! Inserted {} : {}", iter->first, iter->second);

  } else {
    // 4. Failure Case: 'iter' points to the EXISTING entry
    // We can immediately see what the old value was.
    std::println("Skipped. Key '{}' exists with value: {}", iter->first, iter->second);
  }

  return 0;
}
