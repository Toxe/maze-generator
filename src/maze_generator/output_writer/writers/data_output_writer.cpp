#include "data_output_writer.hpp"

void maze_generator::output_writer::DataOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    for (int y = 0; y < size.height; ++y) {
        for (int x = 0; x < size.width; ++x) {
            write(maze.node({x, y}).has_wall(Wall::North) ? 'N' : '-');
            write(maze.node({x, y}).has_wall(Wall::East) ? 'E' : '-');
            write(maze.node({x, y}).has_wall(Wall::South) ? 'S' : '-');
            write(maze.node({x, y}).has_wall(Wall::West) ? 'W' : '-');

            if (x < size.width - 1)
                write('|');
        }

        write('\n');
    }
}
