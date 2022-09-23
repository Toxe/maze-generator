#include "pretty_output_writer.hpp"

void maze_generator::output_writer::PrettyOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    // create grid with wall data
    const int grid_width = 2 * size.width + 1;
    const int grid_height = 2 * size.height + 1;
    std::vector<std::vector<maze::Maze::Node>> grid(static_cast<std::size_t>(grid_height));

    for (std::size_t y = 0; y < static_cast<std::size_t>(grid_height); ++y) {
        grid[y].reserve(static_cast<std::size_t>(grid_width));

        for (std::size_t x = 0; x < static_cast<std::size_t>(grid_width); ++x)
            grid[y].push_back(0);
    }

    for (std::size_t y = 0; y < static_cast<std::size_t>(size.height); ++y) {
        for (std::size_t x = 0; x < static_cast<std::size_t>(size.width); ++x) {
            if (maze.has_wall({x, y}, Wall::North)) {
                grid[2 * y][2 * x] |= static_cast<maze::Maze::Node>(Wall::East);
                grid[2 * y][2 * x + 1] |= static_cast<maze::Maze::Node>(Wall::East) | static_cast<maze::Maze::Node>(Wall::West);
                grid[2 * y][2 * x + 2] |= static_cast<maze::Maze::Node>(Wall::West);
            }

            if (maze.has_wall({x, y}, Wall::East)) {
                grid[2 * y][2 * x + 2] |= static_cast<maze::Maze::Node>(Wall::South);
                grid[2 * y + 1][2 * x + 2] |= static_cast<maze::Maze::Node>(Wall::North) | static_cast<maze::Maze::Node>(Wall::South);
                grid[2 * y + 2][2 * x + 2] |= static_cast<maze::Maze::Node>(Wall::North);
            }

            if (maze.has_wall({x, y}, Wall::South)) {
                grid[2 * y + 2][2 * x] |= static_cast<maze::Maze::Node>(Wall::East);
                grid[2 * y + 2][2 * x + 1] |= static_cast<maze::Maze::Node>(Wall::East) | static_cast<maze::Maze::Node>(Wall::West);
                grid[2 * y + 2][2 * x + 2] |= static_cast<maze::Maze::Node>(Wall::West);
            }

            if (maze.has_wall({x, y}, Wall::West)) {
                grid[2 * y][2 * x] |= static_cast<maze::Maze::Node>(Wall::South);
                grid[2 * y + 1][2 * x] |= static_cast<maze::Maze::Node>(Wall::North) | static_cast<maze::Maze::Node>(Wall::South);
                grid[2 * y + 2][2 * x] |= static_cast<maze::Maze::Node>(Wall::North);
            }
        }
    }

    for (int y = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x) {
            switch (grid[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)]) {
                case 0b0000: write(reinterpret_cast<const char*>(u8"  ")); break;  // |  |
                case 0b0001: write(reinterpret_cast<const char*>(u8"\u2575 ")); break;  // |╵ |
                case 0b0010: write(reinterpret_cast<const char*>(u8" \u2500")); break;  // | ─|
                case 0b0011: write(reinterpret_cast<const char*>(u8"\u2514\u2500")); break;  // |└─|
                case 0b0100: write(reinterpret_cast<const char*>(u8"\u2577 ")); break;  // |╷ |
                case 0b0101: write(reinterpret_cast<const char*>(u8"\u2502 ")); break;  // |│ |
                case 0b0110: write(reinterpret_cast<const char*>(u8"\u250c\u2500")); break;  // |┌─|
                case 0b0111: write(reinterpret_cast<const char*>(u8"\u251C\u2500")); break;  // |├─|
                case 0b1000: write(reinterpret_cast<const char*>(u8"\u2500 ")); break;  // |─ |
                case 0b1001: write(reinterpret_cast<const char*>(u8"\u2518 ")); break;  // |┘ |
                case 0b1010: write(reinterpret_cast<const char*>(u8"\u2500\u2500")); break;  // |──|
                case 0b1011: write(reinterpret_cast<const char*>(u8"\u2534\u2500")); break;  // |┴─|
                case 0b1100: write(reinterpret_cast<const char*>(u8"\u2510 ")); break;  // |┐ |
                case 0b1101: write(reinterpret_cast<const char*>(u8"\u2524 ")); break;  // |┤ |
                case 0b1110: write(reinterpret_cast<const char*>(u8"\u252C\u2500")); break;  // |┬─|
                case 0b1111: write(reinterpret_cast<const char*>(u8"\u253C\u2500")); break;  // |┼─|
            }
        }

        write('\n');
    }
}
