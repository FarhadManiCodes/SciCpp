# HPC & Scientific Library Coding Standards (Trilinos / deal.II Style)

## 1. Memory Management & Ownership
- **Strict Rule:** NEVER use raw `new` or `delete`. Manual memory management is the #1 source of leaks in scientific codes.
- **Preferred Ownership:**
    1. **Stack Allocation:** Fastest. Use for small objects (Points, Tensors, fixed-size vectors).
    2. **`std::unique_ptr`:** Default for dynamic objects. Represents exclusive ownership (e.g., a Solver owns its Preconditioner).
    3. **`std::shared_ptr`:** Use ONLY if ownership is truly shared (mathematically required, e.g., a Mesh shared by two distinct Physics Solvers).
- **Vectors:** Always call `.reserve()` on `std::vector` before filling it in a loop to prevent expensive reallocations.

## 2. Performance & Optimization
- **Const Correctness:** In scientific computing, `const` is not just documentation; it helps the compiler optimize memory loads.
    - *Rule:* Mark every variable `const` unless it strictly needs to change.
    - *Ref:* "If it doesn't change, it's a constant. If you don't say so, you are lying to the compiler."
- **Function Arguments:**
    - **Small Types (int, double, complex):** Pass by `value`.
    - **Large Types (Matrix, Vector, std::string):** Pass by `const &` (const reference) to avoid copying.
- **Inlining:** Define small mathematical functions (dot products, norm calculations) in the header or mark them `inline` (or `[[gnu::always_inline]]` for critical paths).

## 3. Error Handling (HPC Context)
- **Preconditions (Asserts):** Use `assert()` liberally to check mathematical validity (e.g., `assert(v.size() > 0)`, `assert(matrix.rows() == vector.size())`).
    - *Why:* Asserts cost nothing in Release builds but save hours of debugging in Debug builds.
- **Exceptions:** AVOID exceptions for control flow. Use them only for catastrophic runtime failures (e.g., "Singular Matrix" in a solver, "File not found", "Out of Memory").
    - *Trilinos Note:* Don't throw raw `int` or `char*`. Throw `std::runtime_error` or custom scientific exceptions.

## 4. Floating Point Math
- **Equality:** NEVER compare doubles with `==`.
    - *Bad:* `if (x == 0.0)`
    - *Good:* `if (std::abs(x) < 1e-14)` or use a dedicated `almost_equals` function.
- **Precision:** Prefer `double` over `float` unless you have a specific reason (GPU memory constraints or specific reduced-precision solvers).

## 5. Naming Conventions
- **Variables/Functions:** `snake_case` (Standard C++).
    - *Example:* `calculate_residual()`, `matrix_size`.
- **Classes/Types:** `PascalCase`.
    - *Example:* `LinearSolver`, `SparseMatrix`.
- **Member Variables:** Append a trailing underscore `_` to distinguish class members from local variables.
    - *Example:* `double tolerance_;` inside a class.
- **Template Types:** `CamelCase` starting with `T` or distinct name.
    - *Example:* `template <typename ScalarType> class Vector;`
