#include <fstream>
#include <print>
int main() {
  std::ifstream infile("some_missing_file.xyz");

  int i;
  double d;
  infile >> i >> d;
  std::println("i is {}, d is {}", i, d);
  infile.close();
}
