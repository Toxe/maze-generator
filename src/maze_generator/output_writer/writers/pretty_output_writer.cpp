#include <array>

#include "pretty_output_writer.hpp"

namespace maze_generator::output_writer {

void PrettyOutputWriter::output_maze(maze::Maze& maze, int)
{
    const auto size = maze.size();

    // create grid with wall data
    const std::size_t grid_width = 2 * static_cast<std::size_t>(size.width) + 1;
    const std::size_t grid_height = 2 * static_cast<std::size_t>(size.height) + 1;
    std::vector<std::vector<maze::Node>> grid(grid_height);

    for (std::size_t row = 0; row < grid_height; ++row) {
        grid[row].reserve(grid_width);

        for (std::size_t col = 0; col < grid_width; ++col)
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

    // clang-format off
    constexpr std::array blocks = {
        u8"  ",            // 0b0000 |  |
        u8"\u2500 ",       // 0b0001 |─ |
        u8"\u2577 ",       // 0b0010 |╷ |
        u8"\u2510 ",       // 0b0011 |┐ |
        u8" \u2500",       // 0b0100 | ─|
        u8"\u2500\u2500",  // 0b0101 |──|
        u8"\u250c\u2500",  // 0b0110 |┌─|
        u8"\u252C\u2500",  // 0b0111 |┬─|
        u8"\u2575 ",       // 0b1000 |╵ |
        u8"\u2518 ",       // 0b1001 |┘ |
        u8"\u2502 ",       // 0b1010 |│ |
        u8"\u2524 ",       // 0b1011 |┤ |
        u8"\u2514\u2500",  // 0b1100 |└─|
        u8"\u2534\u2500",  // 0b1101 |┴─|
        u8"\u251C\u2500",  // 0b1110 |├─|
        u8"\u253C\u2500",  // 0b1111 |┼─|
    };
    // clang-format on

    for (std::size_t row = 0; row < grid_height; ++row) {
        for (std::size_t col = 0; col < grid_width; ++col)
            write(reinterpret_cast<const char*>(blocks[grid[row][col].value()]));

        write('\n');
    }
}

}  // namespace maze_generator::output_writer
