cmake_minimum_required(VERSION 3.25)
project(SciCore LANGUAGES CXX)

# 1. Shared compiler rules (the "backpack")
add_library(scicore_compiler_flags INTERFACE)
target_compile_features(scicore_compiler_flags INTERFACE cxx_std_26)
target_compile_options(scicore_compiler_flags INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wpedantic -march=native
    >
)

# 2. Global include for mdspan header-only library
target_include_directories(scicore_compiler_flags INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/mdspan
)

# 3. Load helper macros
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(SciCoreHelpers)

# 4. Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 5. Subdirectories
add_subdirectory(src)
add_subdirectory(chapters/chapter_01_basics)
add_subdirectory(playground)
# add_subdirectory(chapters/chapter_02_classes)   # uncomment as you progress
