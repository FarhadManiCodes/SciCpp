#include <print>
void increment(int &x) { x++; }

int main() {
  int i= 4;
  increment(i);
  std::println("i is {}", i);
}
