cmake_minimum_required(VERSION 3.25)
project(SciCore LANGUAGES CXX)

# 1. Shared compiler rules (the "backpack")
# Bare flags without a C++ standard — used when the macro sets the standard per-file.
add_library(scicore_flags_no_std INTERFACE)
target_compile_options(scicore_flags_no_std INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic -march=native
    >
)
target_include_directories(scicore_flags_no_std INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/mdspan
)

# Default C++23 target — inherits the bare flags and adds the standard.
add_library(scicore_compiler_flags INTERFACE)
target_link_libraries(scicore_compiler_flags INTERFACE scicore_flags_no_std)
target_compile_features(scicore_compiler_flags INTERFACE cxx_std_23)

# 2. Global include for mdspan header-only library is set on scicore_flags_no_std above.

# 3. Load helper macros
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(SciCoreHelpers)

# 4. Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 5. Subdirectories
add_subdirectory(src)
add_subdirectory(chapters/chapter_01_basics)
add_subdirectory(playground)
add_subdirectory(chapters/chapter_02_classes)
