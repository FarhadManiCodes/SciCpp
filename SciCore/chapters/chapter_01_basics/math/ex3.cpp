#include <cmath>
#include <numbers>
#include <print>

using std::numbers::pi;

// Clear return type instead of std::pair
struct SolidResult {
  double volume;
  double surface;
};

// Sphere: Calculate surface first, derive volume
[[nodiscard]] auto sphere(double radius) -> SolidResult {
  auto surface= 4.0 * pi * radius * radius;
  auto volume= radius * surface / 3.0;

  return {volume, surface};
}

// Cube: Calculate face area once, reuse - surface before volume
[[nodiscard]] auto cube(double side) -> SolidResult {
  auto face_area= side * side;
  auto surface= 6.0 * face_area;
  auto volume= face_area * side;

  return {volume, surface};
}

// Cylinder: Minimal intermediate variables - surface before volume
[[nodiscard]] auto cylinder(double radius, double height) -> SolidResult {
  auto base_area= pi * radius * radius;

  auto surface= 2.0 * base_area + 2.0 * pi * radius * height;
  auto volume= base_area * height;

  return {volume, surface};
}

// Cone: Simplified lateral surface formula - surface before volume
[[nodiscard]] auto cone(double radius, double height) -> SolidResult {
  auto base_area= pi * radius * radius;
  auto slant= std::hypot(radius, height);

  auto surface= base_area + pi * radius * slant;
  auto volume= base_area * height / 3.0;

  return {volume, surface};
}

// Rectangular prism: Keep only reused variable - surface before volume
[[nodiscard]] auto rectangular_prism(double length, double width, double height) -> SolidResult {
  auto lw= length * width;

  auto surface= 2.0 * (lw + length * height + width * height);
  auto volume= lw * height;

  return {volume, surface};
}

// Pyramid: Use multiplication instead of division - surface before volume
[[nodiscard]] auto pyramid(double length, double width, double height) -> SolidResult {
  auto base_area= length * width;

  auto slant_length= std::hypot(width * 0.5, height);
  auto slant_width= std::hypot(length * 0.5, height);

  auto surface= base_area + length * slant_length + width * slant_width;
  auto volume= base_area * height / 3.0;

  return {volume, surface};
}

// Torus: Derive volume from surface
[[nodiscard]] auto torus(double major_radius, double minor_radius) -> SolidResult {
  auto surface= 4.0 * pi * pi * major_radius * minor_radius;
  auto volume= surface * minor_radius * 0.5;

  return {volume, surface};
}

// Hemisphere: Derive volume from surface
[[nodiscard]] auto hemisphere(double radius) -> SolidResult {
  auto surface= 3.0 * pi * radius * radius;
  auto volume= (2.0 / 9.0) * radius * surface;

  return {volume, surface};
}

// Ellipsoid: Reuse products ab, ac, bc - surface before volume
[[nodiscard]] auto ellipsoid(double a, double b, double c) -> SolidResult {
  auto ab= a * b;
  auto ac= a * c;
  auto bc= b * c;

  constexpr double p= 1.6075;
  constexpr double inv_p= 1.0 / p;

  auto surface=
      4.0 * pi *
      std::pow((std::pow(ab, p) + std::pow(ac, p) + std::pow(bc, p)) * (1.0 / 3.0), inv_p);
  auto volume= (4.0 / 3.0) * pi * ab * c;

  return {volume, surface};
}

int main() {
  std::println("=== Solid Figures: Volume & Surface Area ===\n");

  {
    auto [volume, surface]= sphere(5.0);
    std::println("Sphere (r=5):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= cube(4.0);
    std::println("Cube (a=4):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= cylinder(3.0, 7.0);
    std::println("Cylinder (r=3, h=7):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= cone(4.0, 9.0);
    std::println("Cone (r=4, h=9):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= rectangular_prism(5.0, 3.0, 4.0);
    std::println("Rectangular Prism (l=5, w=3, h=4):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= pyramid(6.0, 6.0, 8.0);
    std::println("Pyramid (l=6, w=6, h=8):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= torus(5.0, 2.0);
    std::println("Torus (R=5, r=2):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= hemisphere(5.0);
    std::println("Hemisphere (r=5):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  {
    auto [volume, surface]= ellipsoid(3.0, 4.0, 5.0);
    std::println("Ellipsoid (a=3, b=4, c=5):");
    std::println("  Volume: {:.2f}", volume);
    std::println("  Surface: {:.2f}\n", surface);
  }

  return 0;
}
