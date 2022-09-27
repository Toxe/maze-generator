#pragma once

#include <random>

#include "node.hpp"
#include "types.hpp"

namespace maze_generator::maze {

class Maze {
public:
    Maze(Size size, int seed);

    [[nodiscard]] Size size() const { return size_; }
    [[nodiscard]] bool valid_coords(Coords coords) const;

    [[nodiscard]] Node& node(Coords coords);

    [[nodiscard]] Coords coords_in_direction(Coords coords, Direction dir) const;
    [[nodiscard]] Wall wall_in_direction(Direction dir) const;
    [[nodiscard]] Direction opposite_direction(Direction dir) const;

    [[nodiscard]] const Direction* random_directions();
    [[nodiscard]] std::random_device::result_type seed() const { return seed_; }

    void clear_walls(Coords orig, Coords dest, Direction dir);

private:
    Size size_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;

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
