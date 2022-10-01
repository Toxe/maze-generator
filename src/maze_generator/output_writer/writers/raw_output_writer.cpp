#include "raw_output_writer.hpp"

#include <iostream>

namespace maze_generator::output_writer {

void RawOutputWriter::output_maze(maze::Maze& maze)
{
    const auto size = maze.size();

    constexpr unsigned char black = 0x00;
    constexpr unsigned char white = 0xff;

    for (int row = 0; row < size.height; ++row) {
        for (int z = 0; z < zoom_; ++z) {
            for (int col = 0; col < size.width; ++col) {
                if (maze.node({col, row}).has_wall(Wall::North)) {
                    write(white, zoom_ * 2);
                } else {
                    write(white, zoom_);
                    write(black, zoom_);
                }
            }

            write(white, zoom_);
        }

        for (int z = 0; z < zoom_; ++z) {
            for (int col = 0; col < size.width; ++col) {
                if (maze.node({col, row}).has_wall(Wall::West)) {
                    write(white, zoom_);
                    write(black, zoom_);
                } else {
                    write(black, zoom_ * 2);
                }
            }

            write(white, zoom_);
        }
    }

    for (int z = 0; z < zoom_; ++z)
        write(white, zoom_ * 2 * size.width + 1);
}

void maze_generator::output_writer::RawOutputWriter::output_info(const maze::Maze& maze)
{
    OutputWriter::output_info(maze);

    const auto size = maze.size();

    std::cout << "image width: " << (zoom_ * (2 * size.width + 1)) << '\n';
    std::cout << "image height: " << (zoom_ * (2 * size.height + 1)) << '\n';
    std::cout << "image format: 1 byte per pixel, grayscale\n";
}

}  // namespace maze_generator::output_writer
