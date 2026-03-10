#include <print>
void swap_readings(double& a, double& b) {
  // 1. Store 'a' in a temp variable.
  double temp= a;
  // 2. Overwrite 'a' with 'b'.
  a= b;
  // 3. Overwrite 'b' with temp.
  b= temp;
}

int main() {
  double a= 1.0;
  double b= 2.0;
  std::println("a = {} and b= {}", a, b);
  swap_readings(a, b);
  std::println("now they have swaped");
  std::println("a = {} and b= {}", a, b);
}
