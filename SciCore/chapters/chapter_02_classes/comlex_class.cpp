#include <print>

class complex {
 public:
  double r, i;
};

int main() {
  complex z, c;
  z.r= 3.5;
  z.i= 2;
  c.r= 2;
  c.i= -3.5;
  std::println("z is {} + {}i", z.r, z.i);
}
