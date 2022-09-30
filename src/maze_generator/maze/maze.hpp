#pragma once

#include <array>
#include <random>

#include "node.hpp"
#include "types.hpp"

namespace maze_generator::maze {

class Maze {
public:
    Maze(Size size, int seed, const Coords& starting_point);

    [[nodiscard]] Size size() const { return size_; }
    [[nodiscard]] bool valid_coords(const Coords& coords) const;

    [[nodiscard]] Node& node(const Coords& coords);

    [[nodiscard]] static Coords coords_in_direction(const Coords& coords, Direction dir);
    [[nodiscard]] static Wall wall_in_direction(Direction dir);
    [[nodiscard]] static Direction opposite_direction(Direction dir);

    [[nodiscard]] const std::array<Direction, 4>& random_directions();
    [[nodiscard]] std::random_device::result_type seed() const { return seed_; }

    void clear_walls(const Coords& from, const Coords& to, Direction dir);

private:
    void generate(const Coords& starting_point);

    Size size_;
    std::vector<Node> nodes_;

    std::random_device random_device_;
    std::random_device::result_type seed_;
    std::mt19937 random_generator_;
    std::uniform_int_distribution<> random_dist_;
};

}  // namespace maze_generator::maze
