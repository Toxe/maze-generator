# executable
add_executable(maze_generator_benchmark
        generate.cpp
        output.cpp
        )

set_target_properties(maze_generator_benchmark PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(maze_generator_benchmark PUBLIC cxx_std_20)
target_compile_options(maze_generator_benchmark PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_libraries(maze_generator_benchmark PRIVATE ${SANITIZER_FLAGS} LIB_maze_generator benchmark::benchmark benchmark::benchmark_main)
