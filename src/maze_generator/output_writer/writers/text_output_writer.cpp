#include "text_output_writer.hpp"

void maze_generator::output_writer::TextOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    for (int y = 0; y < size.height; ++y) {
        for (int x = 0; x < size.width; ++x)
            write(maze.node({x, y}).has_wall(Wall::North) ? "##" : "# ");

        write("#\n");

        for (int x = 0; x < size.width; ++x)
            write(maze.node({x, y}).has_wall(Wall::West) ? "# " : "  ");

        write("#\n");
    }

    for (int x = 0; x < size.width; ++x)
        write("##");

    write("#\n");
}
