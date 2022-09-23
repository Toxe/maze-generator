#pragma once

#include <random>

#include "node.hpp"
#include "types.hpp"

namespace maze_generator::maze {

class Maze {
public:
    Maze(const Size size, const int seed = -1)
        : size_{size},
          nodes_(static_cast<std::size_t>(size_.width * size_.height), Node::with_all_walls()),
          random_device_(),
          random_generator_(random_device_()),
          random_dist_{0, 23}
    {
        seed_ = (seed >= 0) ? static_cast<std::random_device::result_type>(seed) : random_device_();
        random_generator_.seed(seed_);
    }

    [[nodiscard]] Size size() const { return size_; }

    bool valid_coords(const Coords coords) const { return coords.x >= 0 && coords.y >= 0 && coords.x < size_.width && coords.y < size_.height; }

    Coords coords_in_direction(const Coords coords, const Direction dir)
    {
        const Coords offset{direction_coords_offset_[static_cast<int>(dir)]};
        return Coords{coords.x + offset.x, coords.y + offset.y};
    }

    const Direction* random_directions() { return all_possible_random_directions[random_dist_(random_generator_)]; }

    Node& node(const Coords coords) { return nodes_[static_cast<std::size_t>(coords.y * size_.width + coords.x)]; }

    void clear_walls(const Coords orig, const Coords dest, Direction dir)
    {
        const Wall orig_wall = wall_in_direction_[static_cast<int>(dir)];
        const Wall dest_wall = wall_in_direction_[static_cast<int>(opposite_direction_[static_cast<int>(dir)])];

        node(orig).clear_wall(orig_wall);
        node(dest).clear_wall(dest_wall);
    }

    std::random_device::result_type seed() const { return seed_; }

private:
    const Size size_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;

    const Wall wall_in_direction_[4] = {Wall::North, Wall::East, Wall::South, Wall::West};
    const Direction opposite_direction_[4] = {Direction::South, Direction::West, Direction::North, Direction::East};
    const Coords direction_coords_offset_[4] = {Coords{0, -1}, Coords{1, 0}, Coords{0, 1}, Coords{-1, 0}};
    const Direction all_possible_random_directions[24][4] = {
        {Direction::North, Direction::East, Direction::South, Direction::West},
        {Direction::North, Direction::East, Direction::West, Direction::South},
        {Direction::North, Direction::South, Direction::East, Direction::West},
        {Direction::North, Direction::South, Direction::West, Direction::East},
        {Direction::North, Direction::West, Direction::East, Direction::South},
        {Direction::North, Direction::West, Direction::South, Direction::East},
        {Direction::East, Direction::North, Direction::South, Direction::West},
        {Direction::East, Direction::North, Direction::West, Direction::South},
        {Direction::East, Direction::South, Direction::North, Direction::West},
        {Direction::East, Direction::South, Direction::West, Direction::North},
        {Direction::East, Direction::West, Direction::North, Direction::South},
        {Direction::East, Direction::West, Direction::South, Direction::North},
        {Direction::South, Direction::North, Direction::East, Direction::West},
        {Direction::South, Direction::North, Direction::West, Direction::East},
        {Direction::South, Direction::East, Direction::North, Direction::West},
        {Direction::South, Direction::East, Direction::West, Direction::North},
        {Direction::South, Direction::West, Direction::North, Direction::East},
        {Direction::South, Direction::West, Direction::East, Direction::North},
        {Direction::West, Direction::North, Direction::East, Direction::South},
        {Direction::West, Direction::North, Direction::South, Direction::East},
        {Direction::West, Direction::East, Direction::North, Direction::South},
        {Direction::West, Direction::East, Direction::South, Direction::North},
        {Direction::West, Direction::South, Direction::North, Direction::East},
        {Direction::West, Direction::South, Direction::East, Direction::North}};
};

}  // namespace maze_generator::maze
