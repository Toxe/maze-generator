#include "output.hpp"

#include <iostream>

#include "maze.hpp"

namespace maze_generator::maze {

void show_info(const Maze& maze, const OutputFormat output_format, const int zoom)
{
    const auto size = maze.size();

    std::cout << "width: " << size.width << '\n';
    std::cout << "height: " << size.height << '\n';
    std::cout << "seed: " << maze.seed() << '\n';

    if (output_format == OutputFormat::Raw) {
        std::cout << "image width: " << (zoom * (2 * size.width + 1)) << '\n';
        std::cout << "image height: " << (zoom * (2 * size.height + 1)) << '\n';
        std::cout << "image format: 1 byte per pixel, grayscale\n";
    }
}

}  // namespace maze_generator::maze
