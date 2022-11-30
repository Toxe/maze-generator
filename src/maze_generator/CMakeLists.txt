# library
add_library(LIB_maze_generator
        command_line/command_line.cpp
        command_line/command_line.hpp
        include/types.hpp
        logger/logger.cpp
        logger/logger.hpp
        maze/maze.cpp
        maze/maze.hpp
        maze/node.hpp
        output_target/output_target.cpp
        output_target/output_target.hpp
        output_target/targets/byte_output_target.hpp
        output_target/targets/console_output_target.hpp
        output_target/targets/file_output_target.hpp
        output_target/targets/null_output_target.hpp
        output_target/targets/string_output_target.hpp
        output_writer/output_writer.cpp
        output_writer/output_writer.hpp
        output_writer/writers/data_output_writer.cpp
        output_writer/writers/data_output_writer.hpp
        output_writer/writers/pretty_output_writer.cpp
        output_writer/writers/pretty_output_writer.hpp
        output_writer/writers/raw_output_writer.cpp
        output_writer/writers/raw_output_writer.hpp
        output_writer/writers/text_output_writer.cpp
        output_writer/writers/text_output_writer.hpp
        )

set_target_properties(LIB_maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(LIB_maze_generator PUBLIC cxx_std_20)
target_compile_options(LIB_maze_generator PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(LIB_maze_generator PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(LIB_maze_generator PRIVATE ${SANITIZER_LINK_LIBRARIES} CLI11::CLI11 fmt::fmt spdlog::spdlog)
target_include_directories(LIB_maze_generator PUBLIC include)

# executable
add_executable(maze_generator main.cpp)

set_target_properties(maze_generator PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(maze_generator PUBLIC cxx_std_20)
target_compile_options(maze_generator PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(maze_generator PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(maze_generator PRIVATE ${SANITIZER_LINK_LIBRARIES} LIB_maze_generator)
