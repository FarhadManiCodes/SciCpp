#include <print>

int main() {
  const float r1= 3.5, r2= 7.3, pi= 3.14159;

  float area1= pi * r1 * r1;
  std::println("A circle of radius {} has area {}.", r1, area1);
  std::println("The average of {} and {} is {}", r1, r2, (r1 + r2) / 2);
}
