// Requires C++26: std::saturating_cast (<numeric>)
#include <cstdint>
#include <limits>
#include <numeric>
#include <print>
int main()
{
    constexpr std::int16_t x1{696};

    constexpr std::int8_t x2 = std::saturating_cast<std::int8_t>(x1);   // C++26
    constexpr std::int8_t x2s = static_cast<std::int8_t>(x1);
    static_assert(x2 == std::numeric_limits<std::int8_t>::max());
    std::println("static = {}, saturate={}",x2s,x2);

    constexpr std::uint8_t x3 = std::saturating_cast<std::uint8_t>(x1); // C++26
    static_assert(x3 == std::numeric_limits<std::uint8_t>::max());

    constexpr std::int16_t y1{-696};

    constexpr std::int8_t y2 = std::saturating_cast<std::int8_t>(y1);   // C++26
    static_assert(y2 == std::numeric_limits<std::int8_t>::min());

    constexpr std::uint8_t y3 = std::saturating_cast<std::uint8_t>(y1); // C++26
    static_assert(y3 == 0);
}
