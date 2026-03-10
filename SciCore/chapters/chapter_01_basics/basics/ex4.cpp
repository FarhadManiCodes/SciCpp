#include <iostream>

int main() {
  double a, b, c;

  std::cout << "Enter three numbers: ";
  std::cin >> a >> b >> c;
  // Alternative: Using ternary operator (?:)
  double middle= (a >= b && a <= c) || (a <= b && a >= c)   ? a
                 : (b >= a && b <= c) || (b <= a && b >= c) ? b
                                                            : c;

  std::cout << "Middle value: " << middle << std::endl;
}
