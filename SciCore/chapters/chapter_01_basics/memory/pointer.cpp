#include <iomanip>
#include <iostream>

// "Old School" C++ Style (What the book teaches)
// This simulates a C-style API often found in legacy Fortran/C libraries (like
// BLAS)
void calibrate_sensors(double *sensor_data, int num_sensors, double offset) {
  // sensor_data is a POINTER to the first element.

  for (int i= 0; i < num_sensors; ++i) {
    // Pointer Arithmetic:
    // *(sensor_data + i) is the same as sensor_data[i]
    // We are directly modifying the memory at that address.
    *(sensor_data + i)+= offset;
  }
}

int main() {
  // 1. Allocate stack memory (fast, contiguous)
  double temperatures[]= {298.15, 299.5, 300.0, 298.8};

  // 2. Create a pointer to the start of the array
  // The name of an array decays into a pointer to its first element.
  double *ptr_to_start= temperatures;

  std::cout << "Original T[1]: " << *ptr_to_start + 1 << "\n";

  // 3. Pass the pointer to our "solver"
  calibrate_sensors(ptr_to_start, 4, -273.15); // Convert Kelvin to Celsius

  std::cout << "Calibrated T[1]: " << temperatures[1]
            << "\n"; // The original data CHANGED.
}
