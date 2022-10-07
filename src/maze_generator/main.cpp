#include "command_line/command_line.hpp"
#include "maze/maze.hpp"
#include "output_target/output_target.hpp"
#include "output_writer/output_writer.hpp"

int main(int argc, const char* argv[])
{
    const maze_generator::command_line::CommandLine cli({argv, static_cast<std::size_t>(argc)});

    maze_generator::maze::Maze maze(cli.size(), cli.seed(), {0, 0});

    auto output_target = maze_generator::output_target::create_output_target(cli.filename());
    auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, cli.output_format(), cli.zoom());

    if (cli.info())
        output_writer->output_info(maze);

    output_writer->output_maze(maze);
}
