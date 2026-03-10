# scicore_add_exercises(PREFIX)
# Globs all .cpp files in the current directory and creates one
# executable per file, named PREFIX_filename, linked to scicore_compiler_flags.
macro(scicore_add_exercises PREFIX)
    file(GLOB SOURCES "*.cpp")
    foreach(src ${SOURCES})
        get_filename_component(name ${src} NAME_WE)
        add_executable(${PREFIX}_${name} ${src})
        target_link_libraries(${PREFIX}_${name} PRIVATE scicore_compiler_flags)
        target_include_directories(${PREFIX}_${name} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endforeach()
endmacro()
