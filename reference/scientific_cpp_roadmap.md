# Modern Scientific C++ Roadmap (C++20/23/26)

## 1. Data Structures & Linear Algebra (The "HPC Core")
- **Book Context:** The book typically uses `std::vector<std::vector<double>>` (ragged arrays), raw pointers, or custom matrix classes.
- **Modern Replacement (C++23):** STRICTLY use `std::vector<double>` (flat contiguous memory) combined with `std::mdspan` for multi-dimensional views.
    - *Rationale:* This ensures cache locality and allows zero-copy interfacing with C/Fortran libraries.
- **Linear Algebra (C++26):** Watch for `std::linalg` (P1673).
    - *Rule:* If the user writes a raw nested loop for matrix multiplication `C[i][j] += A[i][k] * B[k][j]`, STOP THEM.
    - *Correction:* "This is O(N) and unvectorized. Use `std::linalg::matrix_product` (C++26) or a BLAS library wrapper."
- **Legacy Interop:** When `std::linalg` is unavailable, use `std::mdspan` to view data, then pass `.data_handle()` to standard BLAS functions (like `cblas_dgemm`).
- **Sparse Matrices:** The standard lacks Sparse BLAS. Recommend libraries like Eigen or Blaze, or teach CSR (Compressed Sparse Row) formats using flat `std::vector`s, not linked lists.

## 2. Output & Formatting
- **Book Context:** Uses `std::cout`, `<<` operators, and `std::setprecision`.
- **Modern Replacement (C++23):** Use `std::print` and `std::println`.
    - *Performance:* These are significantly faster than iostreams (no locale/synchronization overhead).
    - *Type Safety:* Compile-time format string checks.
- **Scientific Notation:** Use `std::format("{:.10e}", value)` instead of stream manipulators.

## 3. Concurrency & Parallelism
- **Book Context:** Uses `std::thread`, `std::async`, and `std::mutex`.
- **Modern Replacement (C++20):** Prefer `std::jthread` (automatically joins on destruction) to prevent "terminate called without an active exception" errors.
- **HPC Context:**
    - Mention `std::execution::par_unseq` for parallel algorithms (e.g., `std::transform(std::execution::par_unseq, ...)`).
    - Discuss `std::execution` (Senders/Receivers) as the future C++26 async model for task graphs, replacing raw thread management.

## 4. Mathematical Constants & Functions
- **Book Context:** Defines Pi manually (`3.14159...`) or uses `<cmath>` macros (`M_PI`).
- **Modern Replacement (C++20):** STRICTLY use the `<numbers>` header.
    - *Example:* `std::numbers::pi_v<double>` or `std::numbers::e_v<float>`.
- **Mathematical Functions:** Prefer generic `<cmath>` over type-specific C-names (use `std::abs`, not `fabs`; `std::sin`, not `sinf`).

## 5. Ranges & Views (Data Pipelines)
- **Book Context:** Uses verbose iterator loops (`for(auto it = v.begin(); ...)`).
- **Modern Replacement (C++20/23):** Use `std::ranges` for filtering and transforming data pipelines.
    - *Example:* `auto results = data | std::views::filter(is_positive) | std::views::transform(square);`
    - *HPC Note:* Ranges are expressive but check assembly; for tight inner loops in solvers, traditional index-based loops (compatible with OpenMP/SIMD) may still be preferred until "Parallel Ranges" are fully mature.
