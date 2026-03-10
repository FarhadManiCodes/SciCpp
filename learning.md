# Advanced Math & Linear Algebra Library - Strict Requirements

## 1. Project Goal
Develop a C++23 header-only (or hybrid) mathematical library tailored for high-performance linear algebra. The project serves as a practical implementation of the concepts taught in FAU's *Advanced Programming Techniques* and Peter Gottschling's *Discovering Modern C++*.

## 2. Core Mathematical Domain (Functional Requirements)
* **Dense Linear Algebra:** * Implement a generic $N \times M$ `Matrix` class and an $N$-dimensional `Vector` class.
    * Support basic arithmetic: addition, scaling, inner (dot) products, and matrix-vector / matrix-matrix multiplication.
* **Linear Systems Solvers:**
    * Implement algorithms to solve $Ax = b$.
    * Must include at least two methods: Gaussian Elimination (direct) and Jacobi or Gauss-Seidel (iterative).
* **Data Views:** Implement slicing (e.g., extracting a specific row, column, or sub-matrix without copying the underlying data).

## 3. C++23 Standard & Modern Features
* **Compilation:** Strict `-std=c++23` with `-Wall -Wextra -Wpedantic -Werror` (warnings treated as errors).
* **`std::mdspan`:** The underlying memory of your `Matrix` must be managed using C++23's `<mdspan>` to provide a multi-dimensional view over a flat 1D `std::vector` or raw array.
* **C++20/23 Concepts:** Completely replace SFINAE (`std::enable_if`).
    * Create custom concepts like `template <typename T> concept Numeric = std::is_arithmetic_v<T>;`
    * Enforce constraints on matrix operations (e.g., matrices can only be multiplied if inner dimensions match, enforced via compile-time template constraints where possible).
* **`std::expected` (C++23):** Use this for error handling instead of exceptions for recoverable errors (e.g., returning an error state if a matrix is singular and cannot be inverted).
* **Ranges (`<ranges>`):** Utilize C++20/23 range adaptors for data transformations and view filtering instead of raw `for` loops.

## 4. Advanced C++ Syllabus Requirements
These directly map to the FAU course learning objectives:
* **Expression Templates (Gottschling Book):** * Implement lazy evaluation. An expression like `Vector D = A + B + C;` must compile into a single loop evaluating `D[i] = A[i] + B[i] + C[i];` without creating temporary vectors for `A+B`.
* **Polymorphism Comparison (Dynamic vs. Static):**
    * **Dynamic:** Implement a `LinearSolver` base class with a virtual `solve()` method. Inherit from this for your specific solvers (Strategy Pattern).
    * **Static:** Implement the exact same solvers using the **Curiously Recurring Template Pattern (CRTP)**. 
    * **Objective:** Benchmark both approaches to prove the runtime overhead of virtual table (vtable) lookups versus compile-time resolution.
* **Design Patterns:**
    * **Factory Pattern:** Create a factory that generates matrices initialized with specific conditions (e.g., Identity Matrix, Zero Matrix, Random Matrix).
    * **Iterator Pattern:** Implement custom `begin()` and `end()` iterators for your Matrix class so it works with `std::for_each` and range-based for loops.

## 5. Tooling & DevOps
* **CMake:** Build a modern, target-based CMake environment defining `INTERFACE` or `PUBLIC` libraries.
* **Testing:** GoogleTest or Catch2 integrated via CMake's CTest. Minimum 80% line coverage for the math core.
* **Benchmarking:** Integrate Google Benchmark to mathematically prove that your Expression Templates and CRTP implementations are faster than standard OOP approaches.
* **Memory Safety:** Setup targets to run the test suite through Valgrind or Clang AddressSanitizers (ASan) to guarantee zero memory leaks.
