#include "maze.hpp"

namespace maze_generator::maze {

Maze::Maze(const Size size, const int seed)
    : size_{size},
      nodes_(static_cast<std::size_t>(size_.width * size_.height), Node::with_all_walls()),
      random_device_(),
      seed_((seed >= 0) ? static_cast<std::random_device::result_type>(seed) : random_device_()),
      random_generator_(random_device_()),
      random_dist_{0, 23}
{
    random_generator_.seed(seed_);
}

bool Maze::valid_coords(const Coords coords) const
{
    return coords.x >= 0 && coords.y >= 0 && coords.x < size_.width && coords.y < size_.height;
}

Coords Maze::coords_in_direction(const Coords coords, const Direction dir)
{
    const Coords offset{direction_coords_offset_[static_cast<int>(dir)]};
    return Coords{coords.x + offset.x, coords.y + offset.y};
}

const Direction* Maze::random_directions()
{
    return all_possible_random_directions[random_dist_(random_generator_)];
}

Node& Maze::node(Coords coords)
{
    return nodes_[static_cast<std::size_t>(coords.y * size_.width + coords.x)];
}

void Maze::clear_walls(const Coords orig, const Coords dest, Direction dir)
{
    const Wall orig_wall = wall_in_direction_[static_cast<int>(dir)];
    const Wall dest_wall = wall_in_direction_[static_cast<int>(opposite_direction_[static_cast<int>(dir)])];

    node(orig).clear_wall(orig_wall);
    node(dest).clear_wall(dest_wall);
}

}  // namespace maze_generator::maze
