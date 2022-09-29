#include "text_output_writer.hpp"

namespace maze_generator::output_writer {

void TextOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    for (int row = 0; row < size.height; ++row) {
        for (int col = 0; col < size.width; ++col)
            write(maze.node({col, row}).has_wall(Wall::North) ? "##" : "# ");

        write("#\n");

        for (int col = 0; col < size.width; ++col)
            write(maze.node({col, row}).has_wall(Wall::West) ? "# " : "  ");

        write("#\n");
    }

    for (int col = 0; col < size.width; ++col)
        write("##");

    write("#\n");
}

}  // namespace maze_generator::output_writer
