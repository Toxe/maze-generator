#include <cassert>

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

Node& Maze::node(Coords coords)
{
    return nodes_[static_cast<std::size_t>(coords.y * size_.width + coords.x)];
}

Coords Maze::coords_in_direction(const Coords coords, const Direction dir) const
{
    constexpr std::array direction_coord_offsets{Coords{0, -1}, Coords{1, 0}, Coords{0, 1}, Coords{-1, 0}};

    assert(static_cast<std::size_t>(dir) >= 0);
    assert(static_cast<std::size_t>(dir) < direction_coord_offsets.size());

    const Coords& offset{direction_coord_offsets[static_cast<std::size_t>(dir)]};
    return Coords{coords.x + offset.x, coords.y + offset.y};
}

Wall Maze::wall_in_direction(const Direction dir) const
{
    constexpr std::array walls{Wall::North, Wall::East, Wall::South, Wall::West};

    assert(static_cast<std::size_t>(dir) >= 0);
    assert(static_cast<std::size_t>(dir) < walls.size());

    return walls[static_cast<std::size_t>(dir)];
}

Direction Maze::opposite_direction(const Direction dir) const
{
    constexpr std::array directions{Direction::South, Direction::West, Direction::North, Direction::East};

    assert(static_cast<std::size_t>(dir) >= 0);
    assert(static_cast<std::size_t>(dir) < directions.size());

    return directions[static_cast<std::size_t>(dir)];
}

const std::array<Direction, 4>& Maze::random_directions()
{
    static constexpr std::array all_possible_random_directions{
        std::array<Direction, 4>{Direction::North, Direction::East, Direction::South, Direction::West},
        std::array<Direction, 4>{Direction::North, Direction::East, Direction::West, Direction::South},
        std::array<Direction, 4>{Direction::North, Direction::South, Direction::East, Direction::West},
        std::array<Direction, 4>{Direction::North, Direction::South, Direction::West, Direction::East},
        std::array<Direction, 4>{Direction::North, Direction::West, Direction::East, Direction::South},
        std::array<Direction, 4>{Direction::North, Direction::West, Direction::South, Direction::East},
        std::array<Direction, 4>{Direction::East, Direction::North, Direction::South, Direction::West},
        std::array<Direction, 4>{Direction::East, Direction::North, Direction::West, Direction::South},
        std::array<Direction, 4>{Direction::East, Direction::South, Direction::North, Direction::West},
        std::array<Direction, 4>{Direction::East, Direction::South, Direction::West, Direction::North},
        std::array<Direction, 4>{Direction::East, Direction::West, Direction::North, Direction::South},
        std::array<Direction, 4>{Direction::East, Direction::West, Direction::South, Direction::North},
        std::array<Direction, 4>{Direction::South, Direction::North, Direction::East, Direction::West},
        std::array<Direction, 4>{Direction::South, Direction::North, Direction::West, Direction::East},
        std::array<Direction, 4>{Direction::South, Direction::East, Direction::North, Direction::West},
        std::array<Direction, 4>{Direction::South, Direction::East, Direction::West, Direction::North},
        std::array<Direction, 4>{Direction::South, Direction::West, Direction::North, Direction::East},
        std::array<Direction, 4>{Direction::South, Direction::West, Direction::East, Direction::North},
        std::array<Direction, 4>{Direction::West, Direction::North, Direction::East, Direction::South},
        std::array<Direction, 4>{Direction::West, Direction::North, Direction::South, Direction::East},
        std::array<Direction, 4>{Direction::West, Direction::East, Direction::North, Direction::South},
        std::array<Direction, 4>{Direction::West, Direction::East, Direction::South, Direction::North},
        std::array<Direction, 4>{Direction::West, Direction::South, Direction::North, Direction::East},
        std::array<Direction, 4>{Direction::West, Direction::South, Direction::East, Direction::North}};

    const auto idx = random_dist_(random_generator_);

    assert(static_cast<std::size_t>(idx) >= 0);
    assert(static_cast<std::size_t>(idx) < all_possible_random_directions.size());

    return all_possible_random_directions[static_cast<std::size_t>(idx)];
}

void Maze::clear_walls(const Coords orig, const Coords dest, Direction dir)
{
    const Wall orig_wall = wall_in_direction(dir);
    const Wall dest_wall = wall_in_direction(opposite_direction(dir));

    node(orig).clear_wall(orig_wall);
    node(dest).clear_wall(dest_wall);
}

}  // namespace maze_generator::maze
