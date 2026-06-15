#include <print>
class Vec3 {
 private:
  // SET DEFAULTS HERE
  double x= 0.0;
  double y= 0.0;
  double z= 0.0;

 public:
  // Constructor 1: Overwrites the defaults with user values
  Vec3(double x_in, double y_in, double z_in) : x(x_in), y(y_in), z(z_in) {}

  // Constructor 2: Explicitly uses the defaults defined above
  Vec3()= default;

  void print() const { std::println("({}, {}, {})", x, y, z); }
};
int main() {
  Vec3 v1(1, 2, 3);  // Uses all 3 arguments
  Vec3 v0;           // Uses 0 arguments (defaults to 0,0,0)

  v1.print();
  v0.print();

  return 0;
}
