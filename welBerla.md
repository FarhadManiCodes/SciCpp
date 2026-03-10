# waLBerla Framework - Detailed Architecture Analysis

waLBerla is a massive High-Performance Computing (HPC) framework. Its structure is designed around **strict modularity**—meaning each folder acts as its own self-contained CMake library that can be linked independently. 

Below is a deep dive into how it organizes a C++ project, which serves as a blueprint for professional library design:

## Root Level
* `CMakeLists.txt`: The master build script. It handles compiler flags, C++ standard enforcement, and includes subdirectories.
* `src/`: Contains all library source code.
* `tests/`: Contains all unit tests. **Rule:** The internal structure of `tests/` perfectly mirrors `src/`.
* `apps/`: Contains executable programs that *use* the library (benchmarks, showcases).

## The `src/` Directory (Core Modules)
Instead of a monolithic design, `src/` is broken into distinct domains. Each folder has its own `CMakeLists.txt`.

### 1. `src/core/` (The Foundation)
This module contains everything that doesn't depend on physics or grids.
* `core/math/`: 
    * Contains generic math primitives (Vector3, Matrix3, Quaternions).
    * **Header Design:** Uses `.h` files for declarations and `.impl.h` or `.hpp` for template implementations. (Since templates cannot be compiled into `.cpp` files easily, waLBerla separates the interface from the template logic).
* `core/logging/`: Custom macros and singletons for thread-safe console output.
* `core/debug/`: Assertion macros (`WALBERLA_ASSERT`) that compile out in release mode.

### 2. `src/field/` (Data Structures)
This handles multi-dimensional data grids (the core of any simulation).
* Contains the `GhostLayerField` and `Field` classes. 
* Heavily relies on custom Iterators to allow standard algorithms to traverse 3D grids efficiently.
* Manages memory alignment for SIMD vectorization.

### 3. `src/stencil/` (Metaprogramming)
* Defines grid directions (North, South, East, West).
* Relies heavily on **Template Metaprogramming**. It uses templates to generate highly optimized loops at compile time based on the chosen stencil (e.g., D2Q9 vs D3Q19 in Lattice Boltzmann).

## Testing & Benchmarking (`tests/` and `apps/benchmarks/`)
* **Unit Tests:** Every single class in `src/` has a corresponding `.cpp` file in `tests/` using standard testing frameworks.
* **Benchmarks:** Separated from tests. These executables measure execution time (e.g., memory bandwidth, FLOPs) to ensure new commits don't degrade performance.
