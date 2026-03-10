#include <cmath>
#include <print>
using std::lround;

int main() {
  long l= 1234567890123;
  long l2= static_cast<long>(l + 1.0f - 1.0);  // imprecise
  long l3= lround(1.0f - 1.0) + l;             // correct
  // prinjt
  std::println("l={}\nl2={}\nl3={}", l, l2, l3);
}
