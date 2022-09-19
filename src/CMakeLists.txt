add_subdirectory(maze_generator)

add_executable(maze_generator main.cpp)

set_target_properties(maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(maze_generator PUBLIC cxx_std_20)
target_compile_options(maze_generator PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_include_directories(maze_generator PRIVATE maze_generator/include)
target_link_libraries(maze_generator PRIVATE ${SANITIZER_FLAGS} LIB_maze_generator)
