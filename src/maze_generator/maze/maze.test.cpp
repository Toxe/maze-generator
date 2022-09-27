#include <vector>

#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

#include "generate.hpp"
#include "maze.hpp"

namespace maze_generator::maze {

TEST_CASE("maze::Maze")
{
    SECTION("a newly created Maze has only walls")
    {
        // NESW|NESW|NESW
        // NESW|NESW|NESW
        // NESW|NESW|NESW

        const Size size{3, 3};
        Maze maze{size, 42};

        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x) {
                const auto node = maze.node({x, y});

                CHECK(node.has_wall(Wall::North));
                CHECK(node.has_wall(Wall::East));
                CHECK(node.has_wall(Wall::South));
                CHECK(node.has_wall(Wall::West));
            }
        }
    }

    SECTION("valid_coords()")
    {
        const Maze maze({5, 5}, 42);

        for (int y = 0; y < 5; ++y)
            for (int x = 0; x < 5; ++x)
                CHECK(maze.valid_coords({x, y}));

        CHECK(!maze.valid_coords({-1, 0}));
        CHECK(!maze.valid_coords({0, -1}));
        CHECK(!maze.valid_coords({-1, -1}));

        CHECK(!maze.valid_coords({5, 0}));
        CHECK(!maze.valid_coords({0, 5}));
        CHECK(!maze.valid_coords({5, 5}));
    }

    SECTION("coords_in_direction()")
    {
        const Maze maze({5, 5}, 42);

        CHECK(maze.coords_in_direction({2, 2}, Direction::North) == Coords{2, 1});
        CHECK(maze.coords_in_direction({2, 2}, Direction::East) == Coords{3, 2});
        CHECK(maze.coords_in_direction({2, 2}, Direction::South) == Coords{2, 3});
        CHECK(maze.coords_in_direction({2, 2}, Direction::West) == Coords{1, 2});
    }

    SECTION("wall_in_direction()")
    {
        const Maze maze({5, 5}, 42);

        CHECK(maze.wall_in_direction(Direction::North) == Wall::North);
        CHECK(maze.wall_in_direction(Direction::East) == Wall::East);
        CHECK(maze.wall_in_direction(Direction::South) == Wall::South);
        CHECK(maze.wall_in_direction(Direction::West) == Wall::West);
    }

    SECTION("opposite_direction()")
    {
        const Maze maze({5, 5}, 42);

        CHECK(maze.opposite_direction(Direction::North) == Direction::South);
        CHECK(maze.opposite_direction(Direction::East) == Direction::West);
        CHECK(maze.opposite_direction(Direction::South) == Direction::North);
        CHECK(maze.opposite_direction(Direction::West) == Direction::East);
    }

    SECTION("can remove walls")
    {
        Maze maze{{5, 5}, 42};

        const auto direction = GENERATE(Direction::North, Direction::East, Direction::South, Direction::West);
        const auto coords_in_direction = maze.coords_in_direction({2, 2}, direction);

        maze.clear_walls({2, 2}, coords_in_direction, direction);

        CHECK(!maze.node({2, 2}).has_wall(maze.wall_in_direction(direction)));
        CHECK(!maze.node(coords_in_direction).has_wall(maze.wall_in_direction(maze.opposite_direction(direction))));
    }

    SECTION("can create a Maze (random seed 42)")
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
        auto maze = maze_generator::maze::generate(size, 42, {0, 0});

        const std::vector<std::vector<uint8_t>> grid{
            {0b1011, 0b1010, 0b1010, 0b1100, 0b1101},
            {0b1001, 0b1010, 0b1010, 0b0110, 0b0101},
            {0b0101, 0b1001, 0b1100, 0b1011, 0b0100},
            {0b0101, 0b0101, 0b0011, 0b1010, 0b0100},
            {0b0011, 0b0110, 0b1011, 0b1010, 0b0110},
        };

        for (std::size_t y = 0; y < static_cast<std::size_t>(size.height); ++y)
            for (std::size_t x = 0; x < static_cast<std::size_t>(size.width); ++x)
                CHECK(maze->node({x, y}).value() == grid[y][x]);
    }
}

}  // namespace maze_generator::maze
