set(ALL_TARGETS
    maze_generator
)

add_executable(maze_generator
               maze_generator.cpp
               cli.cpp cli.h)

foreach(target ${ALL_TARGETS})
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(${target} PUBLIC cxx_std_20)
    target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})
    target_link_libraries(${target} PRIVATE ${SANITIZER_FLAGS})
endforeach()

target_link_libraries(maze_generator PRIVATE CLI11::CLI11 fmt::fmt spdlog::spdlog spdlog::spdlog_header_only)
