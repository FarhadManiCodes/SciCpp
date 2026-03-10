#include <iostream>

struct Coordinates {
  double x, y;
};

struct Vertex {
  int id;
  Coordinates coords;  // The vertex HAS coordinates (direct member)
};

struct Triangle {
  // The triangle doesn't OWN the vertex, it just references it
  // because neighbor triangles might share this same vertex.
  Vertex* corner_A;
};

int main() {
  // 1. Setup the data (The "Reality")
  Vertex v1= {101, {0.5, 0.8}};  // ID 101, x=0.5, y=0.8

  // 2. Setup the element (The "Container")
  Triangle t1;
  t1.corner_A= &v1;  // t1 points to v1

  // 3. Create a pointer to the triangle (The "Handle")
  Triangle* mesh_iterator= &t1;

  // --- ACCESSING THE DATA ---

  // We want to access 'x' starting from 'mesh_iterator'.

  // Step 1: mesh_iterator->corner_A
  // Result: We are now at the 'Vertex' address.

  // Step 2: (mesh_iterator->corner_A)->coords
  // Result: We are now looking at the 'Coordinates' struct inside the Vertex.
  // Note: We use '.' here because 'coords' is NOT a pointer inside Vertex.

  // Step 3: Final access
  double val= mesh_iterator->corner_A->coords.x;

  std::cout << "Coordinate X: " << val << "\n";

  return 0;
}
