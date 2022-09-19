#pragma once

namespace maze_generator {

enum class OutputFormat {
    Text,
    Raw,
    Pretty,
    Data
};

enum class Wall {
    North = 0b0001,
    East = 0b0010,
    South = 0b0100,
    West = 0b1000
};

struct Size {
    int width = 0;
    int height = 0;
};

struct Coords {
    int x, y;

    Coords(int point_x, int point_y) : x{point_x}, y{point_y} { }
    Coords(std::size_t point_x, std::size_t point_y) : x{static_cast<int>(point_x)}, y{static_cast<int>(point_y)} { }
};

enum class Direction {
    North = 0,
    East,
    South,
    West
};

}  // namespace maze_generator
