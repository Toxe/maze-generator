#pragma once

#include <random>

#include "cli.hpp"

class Maze {
public:
    using Node = unsigned char;

    enum class Directions { North = 0,
        East,
        South,
        West };
    enum class WallFlags { North = 0b0001,
        East = 0b0010,
        South = 0b0100,
        West = 0b1000 };

    struct Coordinates {
        Coordinates(const int ix, const int iy) : x{ix}, y{iy} { }
        Coordinates(const std::size_t ix, const std::size_t iy) : x{static_cast<int>(ix)}, y{static_cast<int>(iy)} { }
        int x, y;
    };

    Maze(const int width, const int height, const int seed = -1)
        : width_{width},
          height_{height},
          nodes_(static_cast<std::size_t>(width * height), static_cast<Node>(WallFlags::North) | static_cast<Node>(WallFlags::East) | static_cast<Node>(WallFlags::South) | static_cast<Node>(WallFlags::West)),
          random_device_(),
          random_generator_(random_device_()),
          random_dist_{0, 23}
    {
        seed_ = (seed >= 0) ? static_cast<std::random_device::result_type>(seed) : random_device_();
        random_generator_.seed(seed_);
    }

    int width() const { return width_; }
    int height() const { return height_; }

    bool valid_coords(const Coordinates coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < width_ && coords.y < height_; }

    Coordinates coords_in_direction(const Coordinates coords, const Directions dir)
    {
        const Coordinates offset{direction_coords_offset_[static_cast<int>(dir)]};
        return Coordinates{coords.x + offset.x, coords.y + offset.y};
    }

    const Directions* random_directions() { return all_possible_random_directions[random_dist_(random_generator_)]; }

    Node& node(const Coordinates coords) { return nodes_[static_cast<std::size_t>(coords.y * width_ + coords.x)]; }
    bool node_visited(const Coordinates coords) { return node(coords) & 0b10000; }
    void set_node_visited(const Coordinates coords) { node(coords) |= 0b10000; }

    bool has_wall(const Coordinates coords, WallFlags wall) { return node(coords) & static_cast<Node>(wall); }
    void clear_walls(const Coordinates orig, const Coordinates dest, Directions dir)
    {
        const WallFlags orig_wall = wall_in_direction_[static_cast<int>(dir)];
        const WallFlags dest_wall = wall_in_direction_[static_cast<int>(opposite_direction_[static_cast<int>(dir)])];
        node(orig) &= ~(static_cast<Node>(orig_wall));
        node(dest) &= ~(static_cast<Node>(dest_wall));
    }

    std::random_device::result_type seed() const { return seed_; }

private:
    const int width_;
    const int height_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;

    const WallFlags wall_in_direction_[4] = {WallFlags::North, WallFlags::East, WallFlags::South, WallFlags::West};
    const Directions opposite_direction_[4] = {Directions::South, Directions::West, Directions::North, Directions::East};
    const Coordinates direction_coords_offset_[4] = {Coordinates{0, -1}, Coordinates{1, 0}, Coordinates{0, 1}, Coordinates{-1, 0}};
    const Directions all_possible_random_directions[24][4] = {
        {Directions::North, Directions::East, Directions::South, Directions::West},
        {Directions::North, Directions::East, Directions::West, Directions::South},
        {Directions::North, Directions::South, Directions::East, Directions::West},
        {Directions::North, Directions::South, Directions::West, Directions::East},
        {Directions::North, Directions::West, Directions::East, Directions::South},
        {Directions::North, Directions::West, Directions::South, Directions::East},
        {Directions::East, Directions::North, Directions::South, Directions::West},
        {Directions::East, Directions::North, Directions::West, Directions::South},
        {Directions::East, Directions::South, Directions::North, Directions::West},
        {Directions::East, Directions::South, Directions::West, Directions::North},
        {Directions::East, Directions::West, Directions::North, Directions::South},
        {Directions::East, Directions::West, Directions::South, Directions::North},
        {Directions::South, Directions::North, Directions::East, Directions::West},
        {Directions::South, Directions::North, Directions::West, Directions::East},
        {Directions::South, Directions::East, Directions::North, Directions::West},
        {Directions::South, Directions::East, Directions::West, Directions::North},
        {Directions::South, Directions::West, Directions::North, Directions::East},
        {Directions::South, Directions::West, Directions::East, Directions::North},
        {Directions::West, Directions::North, Directions::East, Directions::South},
        {Directions::West, Directions::North, Directions::South, Directions::East},
        {Directions::West, Directions::East, Directions::North, Directions::South},
        {Directions::West, Directions::East, Directions::South, Directions::North},
        {Directions::West, Directions::South, Directions::North, Directions::East},
        {Directions::West, Directions::South, Directions::East, Directions::North}};
};

void generate(Maze& maze, const Maze::Coordinates starting_point);
void output(Maze& maze, const std::string& filename, OutputFormat output_format, int zoom, bool show_info);
