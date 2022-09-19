add_subdirectory(maze_generator)

add_executable(maze_generator main.cpp)

set_target_properties(maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(maze_generator PUBLIC cxx_std_20)
target_compile_options(maze_generator PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_include_directories(maze_generator PRIVATE maze_generator/include)
target_link_libraries(maze_generator PRIVATE ${SANITIZER_FLAGS} LIB_maze_generator)

# ---- Tests ----
if (BUILD_TESTING)
    add_executable(maze_generator_tests
            maze_generator/command_line/command_line.test.cpp
            )

    set_target_properties(maze_generator_tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(maze_generator_tests PUBLIC cxx_std_20)
    target_compile_options(maze_generator_tests PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_include_directories(maze_generator_tests PRIVATE maze_generator/include)
    target_link_libraries(maze_generator_tests PRIVATE ${SANITIZER_FLAGS} LIB_maze_generator Catch2::Catch2WithMain)

    catch_discover_tests(maze_generator_tests)
endif ()
