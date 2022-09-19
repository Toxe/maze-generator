add_library(LIB_maze_generator
        command_line/command_line.cpp
        command_line/command_line.hpp
        generate.cpp
        generate.hpp
        include/types.hpp
        logger/logger.cpp
        logger/logger.hpp
        maze.cpp
        maze.hpp
        output.cpp
        output.hpp
        )

set_target_properties(LIB_maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(LIB_maze_generator PUBLIC cxx_std_20)
target_compile_options(LIB_maze_generator PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_include_directories(LIB_maze_generator PRIVATE include)
target_link_libraries(LIB_maze_generator PRIVATE ${SANITIZER_FLAGS} CLI11::CLI11 fmt::fmt spdlog::spdlog)
