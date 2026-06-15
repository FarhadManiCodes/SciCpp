#include <spdlog/spdlog.h>

int main() {
    // spdlog writes to stdout by default; each call prepends [timestamp] [level].
    spdlog::info("The answer is {}", 6 * 7);
    spdlog::warn("This is a warning: {}", "something looks off");
    spdlog::error("Something went wrong: code {}", 42);

    // debug/trace are silent by default — raise the level to see them.
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Now visible (level raised to debug)");
}
