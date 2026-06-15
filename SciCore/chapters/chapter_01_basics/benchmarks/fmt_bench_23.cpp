// Same output as cout_bench_23.cpp / println_bench_23.cpp, but via upstream
// fmt::println. Races the {fmt} library against the standardized std::println to
// see whether the standard-library version carries overhead vs. its parent.
// Output is byte-identical to the other two (verify with diff).
#include <fmt/base.h>    // fmt::println
#include <fmt/format.h>  // floating-point formatting ({:10.5f})

int main() {
    for (int i = 0; i < 1'000'000; ++i)
        fmt::println("row {:6d}  x = {:10.5f}  tag = {}", i, i * 0.333, "node");
    return 0;
}
