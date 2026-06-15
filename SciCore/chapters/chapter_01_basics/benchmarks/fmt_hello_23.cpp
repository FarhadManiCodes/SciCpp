// Hello-world via {fmt} (target links fmt::fmt). The format-string grammar is
// identical to std::println — only the include and the namespace differ.
// This example is integer-only, so the lightweight <fmt/base.h> suffices;
// floating-point formatting would additionally need <fmt/format.h>.
#include <fmt/base.h>

int main() {
    fmt::println("The answer to the Ultimate Question of Life,\n"
                 "the Universe, and Everything is:\n{}", 6 * 7);
    return 0;
}
