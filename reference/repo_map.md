# Repository Structure Map for "Discovering Modern C++"

The official book examples are organized by C++ Standard version (`c++11`, `c++17`, `c++20`), NOT by Chapter. 
Use this map to locate relevant code when the user refers to a specific chapter.

## Chapter 1: C++ Basics
* **Topics:** Compilation, loops, basic types, IO.
* **Key Folder:** `c++11/`
* **Relevant Files:**
    * `c++11/auto.cpp` (Type deduction)
    * `c++11/range_for.cpp` (Modern loops)
    * `c++03/hello42.cpp` (Basic IO structure)
    * `c++11/limits_example.cpp` (Numeric limits)

## Chapter 2: Classes & Objects
* **Topics:** Constructors, RAII, Rule of Five, Operator Overloading.
* **Key Folders:** `c++11/`, `c++17/`
* **Relevant Files:**
    * `c++11/copy_test.cpp` (Copy semantics)
    * `c++11/move_test.cpp` (Move semantics - Critical)
    * `c++11/complex_test.cpp` (Operator overloading example)
    * `c++11/my_info.hpp` (Header organization)

## Chapter 3: Generic Programming (Templates)
* **Topics:** Function templates, Class templates, Parameter deduction.
* **Key Folders:** `c++14/`, `c++17/`, `c++20/`
* **Relevant Files:**
    * `c++14/auto_decltype.cpp` (Return type deduction)
    * `c++17/folding_example.cpp` (Variadic templates/Fold expressions)
    * `c++20/concepts_*.cpp` (Concepts - The modern way to constrain templates)
    * `c++11/enable_if_*.cpp` (The legacy way - compare with Concepts)

## Chapter 4: Libraries (STL & Ranges)
* **Topics:** Containers, Algorithms, Random Numbers, Ranges.
* **Key Folders:** `c++17/` (Filesystem, Optional), `c++20/` (Ranges)
* **Relevant Files:**
    * `c++20/ranges_*.cpp` (Standard Ranges & Views)
    * `c++17/filesystem_example.cpp`
    * `c++11/random_*.cpp` (Mersenne Twister usage)
    * `c++11/sort_complex_test.cpp` (Sorting custom types)

## Chapter 5: Meta-Programming
* **Topics:** Expression Templates, Compile-time calculation.
* **Key Folders:** `c++11/`, `c++14/`
* **Relevant Files:**
    * `c++11/expression_template_example.cpp` (CRITICAL for scientific efficiency)
    * `c++11/tuple_*.cpp`
    * `c++14/constexpr_example.cpp`

## Chapter 6: Object-Oriented Programming (Inheritance)
* **Topics:** Virtual functions, Abstract classes, Runtime Polymorphism.
* **Key Folders:** `c++03/`, `c++11/`
* **Relevant Files:**
    * `c++11/oop_virtual.cpp`
    * `c++11/inherit_constructor.cpp`

## Chapter 7: Scientific Projects (The "Capstone")
* **Topics:** ODE Solvers, Equation Systems.
* **Key Folders:** `ode_solver/`, `c++11/`
* **Relevant Files:**
    * `ode_solver/` (Contains the full Runge-Kutta implementation)
    * `c++11/gradient_descent_*.cpp`
