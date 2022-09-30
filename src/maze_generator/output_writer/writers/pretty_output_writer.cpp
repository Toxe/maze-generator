#include "pretty_output_writer.hpp"

namespace maze_generator::output_writer {

void PrettyOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    // create grid with wall data
    const int grid_width = 2 * size.width + 1;
    const int grid_height = 2 * size.height + 1;
    std::vector<std::vector<maze::Node>> grid(static_cast<std::size_t>(grid_height));

    for (std::size_t row = 0; row < static_cast<std::size_t>(grid_height); ++row) {
        grid[row].reserve(static_cast<std::size_t>(grid_width));

        for (std::size_t col = 0; col < static_cast<std::size_t>(grid_width); ++col)
            grid[row].push_back(maze::Node{});
    }

    for (std::size_t row = 0; row < static_cast<std::size_t>(size.height); ++row) {
        for (std::size_t col = 0; col < static_cast<std::size_t>(size.width); ++col) {
            const maze::Node& node = maze.node({col, row});

            if (node.has_wall(Wall::North)) {
                grid[2 * row][2 * col].set_wall(Wall::East);
                grid[2 * row][2 * col + 1].set_wall(Wall::East | Wall::West);
                grid[2 * row][2 * col + 2].set_wall(Wall::West);
            }

            if (node.has_wall(Wall::East)) {
                grid[2 * row][2 * col + 2].set_wall(Wall::South);
                grid[2 * row + 1][2 * col + 2].set_wall(Wall::North | Wall::South);
                grid[2 * row + 2][2 * col + 2].set_wall(Wall::North);
            }

            if (node.has_wall(Wall::South)) {
                grid[2 * row + 2][2 * col].set_wall(Wall::East);
                grid[2 * row + 2][2 * col + 1].set_wall(Wall::East | Wall::West);
                grid[2 * row + 2][2 * col + 2].set_wall(Wall::West);
            }

            if (node.has_wall(Wall::West)) {
                grid[2 * row][2 * col].set_wall(Wall::South);
                grid[2 * row + 1][2 * col].set_wall(Wall::North | Wall::South);
                grid[2 * row + 2][2 * col].set_wall(Wall::North);
            }
        }
    }

    for (int row = 0; row < grid_height; ++row) {
        for (int col = 0; col < grid_width; ++col) {
            switch (grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)].value()) {
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
