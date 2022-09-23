#include "raw_output_writer.hpp"

#include <iostream>

void maze_generator::output_writer::RawOutputWriter::output_maze(maze::Maze& maze, int zoom)
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

void maze_generator::output_writer::RawOutputWriter::output_info(const maze::Maze& maze, int zoom)
{
    OutputWriter::output_info(maze, zoom);

    const auto size = maze.size();

    std::cout << "image width: " << (zoom * (2 * size.width + 1)) << '\n';
    std::cout << "image height: " << (zoom * (2 * size.height + 1)) << '\n';
    std::cout << "image format: 1 byte per pixel, grayscale\n";
}
