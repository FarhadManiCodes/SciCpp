# scicore_add_exercises(PREFIX)
# Globs all .cpp files and creates one executable per file, named PREFIX_filename.
# Files with a _20 / _23 / _26 suffix compile at that exact standard;
# all others default to C++23 via scicore_compiler_flags.
macro(scicore_add_exercises PREFIX)
    file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
    foreach(src ${SOURCES})
        get_filename_component(name ${src} NAME_WE)
        add_executable(${PREFIX}_${name} ${src})
        target_include_directories(${PREFIX}_${name} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
        if(name MATCHES "_([0-9][0-9])$")
            # Use the bare-flags target so the standard below is not overridden.
            target_link_libraries(${PREFIX}_${name} PRIVATE scicore_flags_no_std)
            target_compile_features(${PREFIX}_${name} PRIVATE "cxx_std_${CMAKE_MATCH_1}")
        else()
            target_link_libraries(${PREFIX}_${name} PRIVATE scicore_compiler_flags)
        endif()
    endforeach()
endmacro()
