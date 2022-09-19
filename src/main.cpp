#include "maze_generator/command_line/command_line.hpp"
#include "maze_generator/generate.hpp"
#include "maze_generator/output.hpp"

int main(int argc, const char* argv[])
{
    const maze_generator::command_line::CommandLine cli(argc, argv);

    auto maze = maze_generator::generate(cli.size(), cli.seed(), {0, 0});
    maze_generator::output(maze.get(), cli.filename(), cli.output_format(), cli.zoom(), cli.info());
}
