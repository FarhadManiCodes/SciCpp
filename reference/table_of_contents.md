# Book Structure: Discovering Modern C++
Use this Table of Contents to understand the progression of topics and to map user questions to specific book sections.

## Chapter 1: C++ Basics
* **1.1** Our First Program
* **1.2** Variables
    * 1.2.1 Intrinsic Types
    * 1.2.2 Characters and Strings
    * 1.2.3 Declaring Variables
    * 1.2.4 Constants
    * 1.2.5 Literals
    * 1.2.6 Non-narrowing Initialization
    * 1.2.7 Scopes
* **1.3** Operators
    * 1.3.1 Arithmetic Operators
    * 1.3.2 Boolean Operators
    * 1.3.3 Bitwise Operators
    * 1.3.4 Assignment
    * 1.3.5 Program Flow
    * 1.3.6 Memory Handling
    * 1.3.7 Access Operators
    * 1.3.8 Type Handling
    * 1.3.9 Error Handling
    * 1.3.10 Overloading
    * 1.3.11 Operator Precedence
    * 1.3.12 Avoid Side Effects!
* **1.4** Expressions and Statements
    * 1.4.1 Expressions
    * 1.4.2 Statements
    * 1.4.3 Branching
    * 1.4.4 Loops
    * 1.4.5 goto
* **1.5** Functions
    * 1.5.1 Arguments
    * 1.5.2 Returning Results
    * 1.5.3 Inlining
    * 1.5.4 Overloading
    * 1.5.5 main Function
* **1.6** Error Handling
    * 1.6.1 Assertions
    * 1.6.2 Exceptions
    * 1.6.3 Static Assertions
* **1.7** I/O
    * 1.7.1 Standard Output
    * 1.7.2 Standard Input
    * 1.7.3 Input/Output with Files
    * 1.7.4 Generic Stream Concept
    * 1.7.5 Formatting
    * 1.7.6 New Formatting
    * 1.7.7 Dealing with I/O Errors
    * 1.7.8 Filesystem
* **1.8** Arrays, Pointers, and References
    * 1.8.1 Arrays
    * 1.8.2 Pointers
    * 1.8.3 Smart Pointers
    * 1.8.4 References
    * 1.8.5 Comparison between Pointers and References
    * 1.8.6 Do Not Refer to Outdated Data!
    * 1.8.7 Containers for Arrays
* **1.9** Structuring Software Projects
* **1.10** Exercises (Narrowing, Literals, Operators, Branching, Loops, I/O, Arrays, Functions)

## Chapter 2: Classes
* **2.1** Program for Universal Meaning, Not Technical Details
* **2.2** Members (Variables, Accessibility, Access Operators, Static, Functions)
* **2.3** Setting Values: Constructors and Assignments
    * 2.3.1 Constructors
    * 2.3.2 Assignment
    * 2.3.3 Initializer Lists
    * 2.3.4 Uniform Initialization
    * 2.3.5 Move Semantics
    * 2.3.6 Construct Objects from Literals
* **2.4** Destructors (Implementation Rules, Resource Management)
* **2.5** Method Generation Summary
* **2.6** Accessing Member Variables (Access Functions, Subscript Operator, Const Correctness)
* **2.7** Operator Overloading Design
    * 2.7.4 Overloading Equality
    * 2.7.5 Overloading a Spaceship (C++20)
* **2.8** Exercises (Polynomial, Rational, Move Assignment, Resource Rescue)

## Chapter 3: Generic Programming
* **3.1** Function Templates (Instantiation, Deduction, Errors, Uniform Init, Auto Return)
* **3.2** Namespaces and Function Lookup (ADL)
* **3.3** Class Templates
* **3.4** Type Deduction and Definition (Auto, decltype, Template Parameters)
* **3.5** Template Specialization (Partial Specialization, Structured Bindings)
* **3.6** Non-Type Parameters for Templates
* **3.7** Functors (Composition, Recursion, Generic Reduction)
* **3.8** Lambda (Capture, Generic Lambdas)
* **3.9** Variable Templates
* **3.10** Programming with Concepts (Definitions, Dispatching, Design)
* **3.11** Variadic Templates (Recursive Functions, Direct Expansion, Fold Expressions)
* **3.12** Exercises (String Representation, Generic Stack, Tuple Output, Variadic logic)

## Chapter 4: Libraries
* **4.1** Standard Template Library (Iterators, Containers, Algorithms, Ranges, Parallel Computation)
* **4.2** Numerics (Complex Numbers, Random Numbers, Math Constants)
* **4.3** Meta-programming (Limits, Type Traits)
* **4.4** Utilities (optional, tuple, variant, any, string_view, span, function)
* **4.6** Concurrency (Threads, Async, Variadic Mutex, Coroutines)
* **4.7** Scientific Libraries Beyond Standard (Interval Arithmetic, Linear Algebra, ODE/PDE, Graph Algorithms)
* **4.8** Exercises (Sorting, Predicates, Complex Numbers, Parallel Vector Addition)

## Chapter 5: Meta-Programming
* **5.1** Let the Compiler Compute (Compile-Time Functions, Primeness, Constexpr)
* **5.2** Providing and Using Type Information (Type Traits, Conditional Exceptions, enable_if)
* **5.3** Expression Templates (Operator Implementation, Generic ET, Copy Elision)
* **5.4** Meta-Tuning (Unrolling, Nested Unrolling, Dynamic Unrolling)
* **5.5** Optimizing with Semantic Concepts
* **5.6** Turing Completeness
* **5.7** Exercises (Fibonacci, GCD, Vector Expression Templates, Meta-List)

## Chapter 6: Object-Oriented Programming
* **6.1** Basic Principles (Inheritance, Virtual Functions, Functors via Inheritance)
* **6.2** Removing Redundancy
* **6.3** Multiple Inheritance (Diamond Problem)
* **6.4** Dynamic Selection by Sub-typing
* **6.5** Conversion (Casts, Implicit Conversions)
* **6.6** Advanced Techniques (CRTP, Type Traits with Overloading)
* **6.7** Exercises (Diamond Shape, Inheritance Vector Class, Cloning)

## Chapter 7: Scientific Projects
* **7.1** Implementation of ODE Solvers (Runge-Kutta, Generic Implementation)
* **7.2** Creating Projects (Build Process, CMake/Make)
* **7.3** Modules
* **A-C** Appendices (Clumsy Stuff, Tools, Language Definitions)
