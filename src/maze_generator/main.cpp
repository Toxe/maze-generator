#include "command_line/command_line.hpp"
#include "maze/generate.hpp"
#include "maze/output.hpp"

int main(int argc, const char* argv[])
{
    const maze_generator::command_line::CommandLine cli(argc, argv);

    auto maze = maze_generator::maze::generate(cli.size(), cli.seed(), {0, 0});
    maze_generator::maze::output(maze.get(), cli.filename(), cli.output_format(), cli.zoom(), cli.info());
}
