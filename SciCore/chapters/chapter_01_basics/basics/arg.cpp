#include <charconv>     // Core engine
#include <cstdlib>      // for std::exit
#include <optional>     // clean return type
#include <print>        // C++23: You have this!
#include <span>         // clean array access
#include <string_view>  // Zero-copy string
#include <system_error>

// A zero-overhead wrapper to make usage clean
[[nodiscard]] std::optional<double> to_double(std::string_view sv) noexcept {
  double value;
  const auto end= sv.data() + sv.size();
  auto [ptr, ec]= std::from_chars(sv.data(), end, value);

  if (ec != std::errc() || ptr != end) {
    return std::nullopt;
  }
  return value;
}

int main(int argc, char* argv[]) {
  std::span args(argv, argc);

  if (argc < 3) {
    std::println(stderr, "Usage: {} <num1> <num2>", args[0]);
    return 1;
  }

  // Monadic style: handle errors inline with or_else
  auto val1= to_double(args[1]).or_else([&]() -> std::optional<double> {
    std::println(stderr, "Error: '{}' is not a valid number.", args[1]);
    std::exit(1);
  });

  auto val2= to_double(args[2]).or_else([&]() -> std::optional<double> {
    std::println(stderr, "Error: '{}' is not a valid number.", args[2]);
    std::exit(1);
  });

  // At this point, both are guaranteed to have values
  std::println("Result: {}", *val1 + *val2);
  return 0;
}
