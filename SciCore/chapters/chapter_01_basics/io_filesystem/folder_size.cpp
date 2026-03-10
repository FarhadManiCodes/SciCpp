#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <print>

namespace fs= std::filesystem;

std::uintmax_t get_directory_size(const fs::path& path) {
  // 1. Guard Clause: Handle invalid paths immediately
  [[unlikely]] if (!fs::exists(path) || !fs::is_directory(path)) { return 0; }

  // 2. Define the helper lambda separately
  auto add_file_size= [](std::uintmax_t current_sum, const fs::directory_entry& entry) {
    [[likely]] if (entry.is_regular_file()) { return current_sum + entry.file_size(); }
    return current_sum;  // If directory or special file, add nothing
  };

  // 3. Execute the logic
  // Now the actual operation is very short and descriptive
  return std::ranges::fold_left(fs::recursive_directory_iterator(path), 0ULL, add_file_size);
}
int main() {
  fs::path myDir= "/home/farhad/learning/c++";

  if (fs::exists(myDir)) {
    std::uintmax_t bytes= get_directory_size(myDir);

    // C++23 std::println automatically handles types and adds a newline
    std::println("Total size: {} bytes", bytes);

    // You can format floats easily (e.g., {:.2f} for 2 decimal places)
    std::println("Total size: {:.2f} MB", static_cast<double>(bytes) / 1024.0 / 1024.0);

  } else {
    std::println(stderr, "Directory not found: {}", myDir.string());
  }

  return 0;
}
