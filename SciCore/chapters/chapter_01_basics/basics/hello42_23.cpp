#include <print>

int main() {
    // ONE call. Atomic. Fast. Clean.
    std::println("The answer to the Ultimate Question of Life,\n"
                 "the Universe, and Everything is:\n{}", 6 * 7);

    std::println("this is a test\n1\n2\n3");

    std::println(R"(The answer to the Ultimate Question of Life,
the Universe, and Everything is:
{})", 6 * 7);

    return 0;
}
