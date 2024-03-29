# tests
if (BUILD_TESTING)
    add_executable(maze_generator_tests
            ../maze_generator/command_line/command_line.test.cpp
            ../maze_generator/maze/maze.test.cpp
            ../maze_generator/maze/node.test.cpp
            ../maze_generator/output_target/output_target.test.cpp
            ../maze_generator/output_writer/output_writer.test.cpp
            )

    set_target_properties(maze_generator_tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(maze_generator_tests PUBLIC cxx_std_20)
    target_compile_options(maze_generator_tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(maze_generator_tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(maze_generator_tests PRIVATE ${SANITIZER_LINK_LIBRARIES} LIB_maze_generator Catch2::Catch2WithMain)

    catch_discover_tests(maze_generator_tests)
endif ()
