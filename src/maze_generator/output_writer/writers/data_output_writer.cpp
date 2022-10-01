#include "data_output_writer.hpp"

namespace maze_generator::output_writer {

void DataOutputWriter::output_maze(maze::Maze& maze)
{
    const auto size = maze.size();

    for (int row = 0; row < size.height; ++row) {
        for (int col = 0; col < size.width; ++col) {
            const maze::Node& node = maze.node({col, row});

            write(node.has_wall(Wall::North) ? 'N' : '-');
            write(node.has_wall(Wall::East) ? 'E' : '-');
            write(node.has_wall(Wall::South) ? 'S' : '-');
            write(node.has_wall(Wall::West) ? 'W' : '-');

            if (col < size.width - 1)
                write('|');
        }

        write('\n');
    }
}

}  // namespace maze_generator::output_writer
