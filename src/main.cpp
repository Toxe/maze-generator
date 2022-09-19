#include "maze_generator/command_line/command_line.hpp"
#include "maze_generator/maze_generator.hpp"

int main(int argc, const char* argv[])
{
    maze_generator::command_line::CommandLine cli(argc, argv);

    maze_generator::maze_generator::Maze maze(cli.size(), cli.seed());

    generate(maze, {0, 0});
    output(maze, cli.filename(), cli.output_format(), cli.zoom(), cli.info());
}
