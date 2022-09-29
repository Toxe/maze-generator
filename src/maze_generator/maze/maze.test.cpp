#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

#include "maze.hpp"

namespace maze_generator::maze {

constexpr int test_random_seed = 42;
constexpr maze_generator::Coords test_starting_point{0, 0};

TEST_CASE("maze::Maze")
{
    SECTION("valid_coords()")
    {
        const Size size{5, 5};
        const Maze maze(size, test_random_seed, test_starting_point);

        for (int row = 0; row < size.height; ++row)
            for (int col = 0; col < size.width; ++col)
                CHECK(maze.valid_coords({col, row}));

        CHECK(!maze.valid_coords({-1, 0}));
        CHECK(!maze.valid_coords({0, -1}));
        CHECK(!maze.valid_coords({-1, -1}));

        CHECK(!maze.valid_coords({5, 0}));
        CHECK(!maze.valid_coords({0, 5}));
        CHECK(!maze.valid_coords({5, 5}));
    }

    SECTION("coords_in_direction()")
    {
        const Maze maze({5, 5}, test_random_seed, test_starting_point);

        CHECK(maze.coords_in_direction({2, 2}, Direction::North) == Coords{2, 1});
        CHECK(maze.coords_in_direction({2, 2}, Direction::East) == Coords{3, 2});
        CHECK(maze.coords_in_direction({2, 2}, Direction::South) == Coords{2, 3});
        CHECK(maze.coords_in_direction({2, 2}, Direction::West) == Coords{1, 2});
    }

    SECTION("wall_in_direction()")
    {
        const Maze maze({5, 5}, test_random_seed, test_starting_point);

        CHECK(maze.wall_in_direction(Direction::North) == Wall::North);
        CHECK(maze.wall_in_direction(Direction::East) == Wall::East);
        CHECK(maze.wall_in_direction(Direction::South) == Wall::South);
        CHECK(maze.wall_in_direction(Direction::West) == Wall::West);
    }

    SECTION("opposite_direction()")
    {
        const Maze maze({5, 5}, test_random_seed, test_starting_point);

        CHECK(maze.opposite_direction(Direction::North) == Direction::South);
        CHECK(maze.opposite_direction(Direction::East) == Direction::West);
        CHECK(maze.opposite_direction(Direction::South) == Direction::North);
        CHECK(maze.opposite_direction(Direction::West) == Direction::East);
    }

    SECTION("can remove walls")
    {
        Maze maze{{5, 5}, test_random_seed, test_starting_point};

        const auto direction = GENERATE(Direction::North, Direction::East, Direction::South, Direction::West);
        const auto coords_in_direction = maze.coords_in_direction({2, 2}, direction);

        maze.clear_walls({2, 2}, coords_in_direction, direction);

        CHECK(!maze.node({2, 2}).has_wall(maze.wall_in_direction(direction)));
        CHECK(!maze.node(coords_in_direction).has_wall(maze.wall_in_direction(maze.opposite_direction(direction))));
    }

    SECTION("can create a Maze")
    {
        // ┌───────────────┬───┐
        // │               │   │
        // ├────────────   │   │
        // │               │   │
        // │   ┌───────┬───┘   │
        // │   │       │       │
        // │   │   ╷   └────   │
        // │   │   │           │
        // │   ╵   ├────────   │
        // │       │           │
        // └───────┴───────────┘

        // N-SW|N-S-|N-S-|NE--|NE-W
        // N--W|N-S-|N-S-|-ES-|-E-W
        // -E-W|N--W|NE--|N-SW|-E--
        // -E-W|-E-W|--SW|N-S-|-E--
        // --SW|-ES-|N-SW|N-S-|-ES-

        const Size size{5, 5};
        Maze maze(size, test_random_seed, test_starting_point);

        const std::vector<std::vector<uint8_t>> grid{
            {0b1011, 0b1010, 0b1010, 0b1100, 0b1101},
            {0b1001, 0b1010, 0b1010, 0b0110, 0b0101},
            {0b0101, 0b1001, 0b1100, 0b1011, 0b0100},
            {0b0101, 0b0101, 0b0011, 0b1010, 0b0100},
            {0b0011, 0b0110, 0b1011, 0b1010, 0b0110},
        };

        for (std::size_t row = 0; row < static_cast<std::size_t>(size.height); ++row)
            for (std::size_t col = 0; col < static_cast<std::size_t>(size.width); ++col)
                CHECK(maze.node({col, row}).value() == grid[row][col]);
    }
}

}  // namespace maze_generator::maze
