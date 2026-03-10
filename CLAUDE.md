# CLAUDE.md

This file provides guidance to Claude Code when working in the SciCpp repository.

## Repository Overview

A unified C++ learning and library workspace:

- **`reference/`** — Original dmc2 book examples (C++03–C++20, read-only study material)
- **`SciCore/`** — Personal C++23/26 exercises and growing library following *Discovering Modern C++* (Gottschling, 2nd ed.)
- **`learning.md`** — Project spec for the planned C++23 high-performance linear algebra library
- **`welBerla.md`** — Architecture reference notes on the waLBerla HPC framework

## Build Commands

### SciCore (exercises + library)
```bash
cd SciCore
cmake -B build -S .
cmake --build build

# Build a single target
cmake --build build --target ch01_memory_matrix_perf
```

### Reference examples (independent build system)
```bash
cd reference
cmake -B build -S .
cmake --build build
# Enable C++20 examples:
cmake -B build -S . -DDMC2_ENABLE_CPP20=ON
```

## Compiler & Standard

- **Standard:** C++23 (`cxx_std_23` via `target_compile_features`), extensions off.
- **Flags:** `-Wall -Wextra -Wpedantic -march=native` (no `-Werror`).
- **`compile_commands.json`** exported automatically for clangd.
- **External dep:** `mdspan` header-only library in `SciCore/external/mdspan/` — included via `scicore_compiler_flags` interface target.

## CMake Architecture

The SciCore build uses a **waLBerla-inspired** structure:

- `SciCore/CMakeLists.txt` — master, defines `scicore_compiler_flags` interface target
- `SciCore/cmake/SciCoreHelpers.cmake` — provides `scicore_add_exercises(PREFIX)` macro
- `SciCore/src/` — growing reusable library (placeholder, add `add_subdirectory` as components are extracted)
- `SciCore/chapters/chapter_NN_name/` — one subdir per book chapter, each with a `CMakeLists.txt`
- `SciCore/playground/` — scratch experiments

### Adding a new chapter or topic
1. Create `chapters/chapter_NN_name/topic/` with your `.cpp` files.
2. Add a `CMakeLists.txt` containing: `scicore_add_exercises(chNN_topic)`
3. Add `add_subdirectory(topic)` in the parent chapter `CMakeLists.txt`.
4. Uncomment (or add) the chapter in `SciCore/CMakeLists.txt`.

## Coding Standards

- **Naming:** `snake_case` for variables/functions, `PascalCase` for classes/types, trailing `_` for class members (e.g., `tolerance_`), `CamelCase` template type params (e.g., `ScalarType`).
- **Memory:** No raw `new`/`delete`. Prefer stack → `unique_ptr` → `shared_ptr`. Call `.reserve()` before filling vectors.
- **Const correctness:** Mark everything `const` unless it must change.
- **Function args:** pass small types by value; large types by `const&`.
- **Error handling:** `assert()` for preconditions; exceptions for catastrophic failures; prefer `std::expected` (C++23) for recoverable errors.
- **Floating point:** Never compare doubles with `==`; use `std::abs(x - y) < 1e-14`.

## Planned Library Architecture (`learning.md`)

- `Matrix<N,M>` / `Vector<N>` backed by `std::mdspan` over a flat `std::vector`
- Custom C++20 Concepts replacing all SFINAE
- Expression Templates for lazy evaluation (zero temporaries on `D = A + B + C`)
- Dynamic polymorphism (`LinearSolver` base + virtual `solve()`) **and** static CRTP versions, with Google Benchmark comparisons
- Factory Pattern for matrix initialization; custom iterators
- GoogleTest or Catch2 via CTest; Valgrind/ASan targets
