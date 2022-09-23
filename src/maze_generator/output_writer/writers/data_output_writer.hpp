#pragma once

#include "../output_writer.hpp"

namespace maze_generator::output_writer {

class DataOutputWriter : public OutputWriter {
public:
    explicit DataOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }

    virtual void output_maze(maze::Maze& maze, int) override
    {
        const auto size = maze.size();

        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x) {
                write(maze.has_wall({x, y}, Wall::North) ? 'N' : '-');
                write(maze.has_wall({x, y}, Wall::East) ? 'E' : '-');
                write(maze.has_wall({x, y}, Wall::South) ? 'S' : '-');
                write(maze.has_wall({x, y}, Wall::West) ? 'W' : '-');

                if (x < size.width - 1)
                    write('|');
            }

            write('\n');
        }
    }
};

}  // namespace maze_generator::output_writer
