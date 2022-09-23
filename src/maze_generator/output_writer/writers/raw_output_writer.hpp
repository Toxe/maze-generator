#pragma once

#include "../output_writer.hpp"

namespace maze_generator::output_writer {

class RawOutputWriter : public OutputWriter {
public:
    explicit RawOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }

    virtual void output_maze(maze::Maze& maze, int zoom) override
    {
        const auto size = maze.size();

        const unsigned char black = 0x00;
        const unsigned char white = 0xff;

        for (int y = 0; y < size.height; ++y) {
            for (int r = 0; r < zoom; ++r) {
                for (int x = 0; x < size.width; ++x) {
                    if (maze.has_wall({x, y}, Wall::North)) {
                        for (int z = 0; z < zoom; ++z) {
                            write(white);
                            write(white);
                        }
                    } else {
                        for (int z = 0; z < zoom; ++z)
                            write(white);

                        for (int z = 0; z < zoom; ++z)
                            write(black);
                    }
                }

                for (int z = 0; z < zoom; ++z)
                    write(white);
            }

            for (int r = 0; r < zoom; ++r) {
                for (int x = 0; x < size.width; ++x) {
                    if (maze.has_wall({x, y}, Wall::West)) {
                        for (int z = 0; z < zoom; ++z)
                            write(white);

                        for (int z = 0; z < zoom; ++z)
                            write(black);
                    } else {
                        for (int z = 0; z < zoom; ++z) {
                            write(black);
                            write(black);
                        }
                    }
                }

                for (int z = 0; z < zoom; ++z)
                    write(white);
            }
        }

        for (int r = 0; r < zoom; ++r) {
            for (int x = 0; x < size.width; ++x)
                for (int z = 0; z < zoom; ++z) {
                    write(white);
                    write(white);
                }

            for (int z = 0; z < zoom; ++z)
                write(white);
        }
    }
};

}  // namespace maze_generator::output_writer
