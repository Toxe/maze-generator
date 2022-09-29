#include "pretty_output_writer.hpp"

namespace maze_generator::output_writer {

void PrettyOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    // create grid with wall data
    const int grid_width = 2 * size.width + 1;
    const int grid_height = 2 * size.height + 1;
    std::vector<std::vector<maze::Node>> grid(static_cast<std::size_t>(grid_height));

    for (std::size_t y = 0; y < static_cast<std::size_t>(grid_height); ++y) {
        grid[y].reserve(static_cast<std::size_t>(grid_width));

        for (std::size_t x = 0; x < static_cast<std::size_t>(grid_width); ++x)
            grid[y].push_back(maze::Node{});
    }

    for (std::size_t y = 0; y < static_cast<std::size_t>(size.height); ++y) {
        for (std::size_t x = 0; x < static_cast<std::size_t>(size.width); ++x) {
            if (maze.node({x, y}).has_wall(Wall::North)) {
                grid[2 * y][2 * x].set_wall(Wall::East);
                grid[2 * y][2 * x + 1].set_wall(Wall::East | Wall::West);
                grid[2 * y][2 * x + 2].set_wall(Wall::West);
            }

            if (maze.node({x, y}).has_wall(Wall::East)) {
                grid[2 * y][2 * x + 2].set_wall(Wall::South);
                grid[2 * y + 1][2 * x + 2].set_wall(Wall::North | Wall::South);
                grid[2 * y + 2][2 * x + 2].set_wall(Wall::North);
            }

            if (maze.node({x, y}).has_wall(Wall::South)) {
                grid[2 * y + 2][2 * x].set_wall(Wall::East);
                grid[2 * y + 2][2 * x + 1].set_wall(Wall::East | Wall::West);
                grid[2 * y + 2][2 * x + 2].set_wall(Wall::West);
            }

            if (maze.node({x, y}).has_wall(Wall::West)) {
                grid[2 * y][2 * x].set_wall(Wall::South);
                grid[2 * y + 1][2 * x].set_wall(Wall::North | Wall::South);
                grid[2 * y + 2][2 * x].set_wall(Wall::North);
            }
        }
    }

    for (int y = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x) {
            switch (grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)].value()) {
                case 0b0000: write(reinterpret_cast<const char*>(u8"  ")); break;  // |  |
                case 0b0001: write(reinterpret_cast<const char*>(u8"\u2500 ")); break;  // |─ |
                case 0b0010: write(reinterpret_cast<const char*>(u8"\u2577 ")); break;  // |╷ |
                case 0b0011: write(reinterpret_cast<const char*>(u8"\u2510 ")); break;  // |┐ |
                case 0b0100: write(reinterpret_cast<const char*>(u8" \u2500")); break;  // | ─|
                case 0b0101: write(reinterpret_cast<const char*>(u8"\u2500\u2500")); break;  // |──|
                case 0b0110: write(reinterpret_cast<const char*>(u8"\u250c\u2500")); break;  // |┌─|
                case 0b0111: write(reinterpret_cast<const char*>(u8"\u252C\u2500")); break;  // |┬─|
                case 0b1000: write(reinterpret_cast<const char*>(u8"\u2575 ")); break;  // |╵ |
                case 0b1001: write(reinterpret_cast<const char*>(u8"\u2518 ")); break;  // |┘ |
                case 0b1010: write(reinterpret_cast<const char*>(u8"\u2502 ")); break;  // |│ |
                case 0b1011: write(reinterpret_cast<const char*>(u8"\u2524 ")); break;  // |┤ |
                case 0b1100: write(reinterpret_cast<const char*>(u8"\u2514\u2500")); break;  // |└─|
                case 0b1101: write(reinterpret_cast<const char*>(u8"\u2534\u2500")); break;  // |┴─|
                case 0b1110: write(reinterpret_cast<const char*>(u8"\u251C\u2500")); break;  // |├─|
                case 0b1111: write(reinterpret_cast<const char*>(u8"\u253C\u2500")); break;  // |┼─|
            }
        }

        write('\n');
    }
}

}  // namespace maze_generator::output_writer
