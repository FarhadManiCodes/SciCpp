scicore_add_exercises(ch01_benchmarks)

# Benchmark targets are always built with -O3, independent of CMAKE_BUILD_TYPE,
# so timings are meaningful even in the default (unoptimized) configuration.
# Any source with "fmt" in its name also links the {fmt} library.
find_package(fmt REQUIRED)
file(GLOB _bench_srcs CONFIGURE_DEPENDS "*.cpp")
foreach(_src ${_bench_srcs})
    get_filename_component(_name ${_src} NAME_WE)
    target_compile_options(ch01_benchmarks_${_name} PRIVATE -O3)
    if(_name MATCHES "fmt")
        target_link_libraries(ch01_benchmarks_${_name} PRIVATE fmt::fmt)
    endif()
endforeach()
