#include "maze_generator/cli.hpp"
#include "maze_generator/maze_generator.hpp"

int main(int argc, char* argv[])
{
    auto [seed, width, height, filename, output_format, zoom, info] = eval_args(argc, argv);
    Maze maze(width, height, seed);

    generate(maze, {0, 0});
    output(maze, filename, output_format, zoom, info);
}
