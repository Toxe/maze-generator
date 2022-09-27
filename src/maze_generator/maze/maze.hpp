#pragma once

#include <array>
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

    [[nodiscard]] const std::array<Direction, 4>& random_directions();
    [[nodiscard]] std::random_device::result_type seed() const { return seed_; }

    void clear_walls(Coords orig, Coords dest, Direction dir);

private:
    Size size_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;
};

}  // namespace maze_generator::maze
