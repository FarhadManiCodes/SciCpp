#include <print>

int main() {
  // ONE call. Atomic. Fast. Clean.
  std::println(
      "The answer to the Ultimate Question of Life,\n"
      "the Universe, and Everything is:\n{}",
      6 * 7);

  return 0;
}
