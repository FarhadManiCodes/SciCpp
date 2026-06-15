// Same formatted output as println_bench_23.cpp, but via std::cout. Kept C++23 so
// the only difference between the two is the output method (not the language level).
// '\n' (not std::endl) avoids per-line flushing — that flush cost is a separate
// experiment. Try ios_base::sync_with_stdio(false) to see cout speed up.
#include <iostream>
#include <iomanip>

int main() {
    for (int i = 0; i < 1'000'000; ++i)
        std::cout << "row " << std::setw(6) << i
                  << "  x = " << std::fixed << std::setprecision(5) << std::setw(10) << i * 0.333
                  << "  tag = node\n";
    return 0;
}
