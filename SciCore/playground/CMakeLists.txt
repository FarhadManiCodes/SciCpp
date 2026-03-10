# gradient.cpp is a library snippet (no main), skip it
list(APPEND SCICORE_PLAYGROUND_EXCLUDE gradient.cpp)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    if(NOT "${name}.cpp" IN_LIST SCICORE_PLAYGROUND_EXCLUDE)
        add_executable(playground_${name} ${src})
        target_link_libraries(playground_${name} PRIVATE scicore_compiler_flags)
        target_include_directories(playground_${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
endforeach()
