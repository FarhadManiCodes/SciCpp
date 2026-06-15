// Formatted output via std::println (C++23). Compared against cout_bench_23.cpp.
// Both produce byte-identical output so the only variable measured is the
// output/formatting mechanism. Run under hyperfine; verify equality with diff.
#include <print>

int main() {
    for (int i = 0; i < 1'000'000; ++i)
        std::println("row {:6d}  x = {:10.5f}  tag = {}", i, i * 0.333, "node");
    return 0;
}
