#pragma once

#include "../output_writer.hpp"

namespace maze_generator::output_writer {

class TextOutputWriter : public OutputWriter {
public:
    explicit TextOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }

    virtual void output_maze(maze::Maze& maze, int) override
    {
        const auto size = maze.size();

        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x)
                write(maze.has_wall({x, y}, Wall::North) ? "##" : "# ");

            write("#\n");

            for (int x = 0; x < size.width; ++x)
                write(maze.has_wall({x, y}, Wall::West) ? "# " : "  ");

            write("#\n");
        }

        for (int x = 0; x < size.width; ++x)
            write("##");

        write("#\n");
    }
};

}  // namespace maze_generator::output_writer
