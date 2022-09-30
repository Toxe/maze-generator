#include "maze.hpp"

namespace maze_generator::maze {

Maze::Maze(const Size size, const int seed, const Coords& starting_point)
    : size_{size},
      nodes_(static_cast<std::size_t>(size_.width * size_.height), Node::with_all_walls()),
      seed_((seed >= 0) ? static_cast<std::random_device::result_type>(seed) : random_device_()),
      random_generator_(random_device_()),
      random_dist_{0, 23}
{
    generate(starting_point);
}

bool Maze::valid_coords(const Coords& coords) const
{
    return coords.x >= 0 && coords.y >= 0 && coords.x < size_.width && coords.y < size_.height;
}

Node& Maze::node(const Coords& coords)
{
    return nodes_[static_cast<std::size_t>(coords.y * size_.width + coords.x)];
}

Coords Maze::coords_in_direction(const Coords& coords, const Direction dir)
{
    constexpr std::array direction_coord_offsets{Coords{0, -1}, Coords{1, 0}, Coords{0, 1}, Coords{-1, 0}};

    const Coords& offset{direction_coord_offsets[static_cast<std::size_t>(dir)]};
    return Coords{coords.x + offset.x, coords.y + offset.y};
}

Wall Maze::wall_in_direction(const Direction dir)
{
    constexpr std::array walls{Wall::North, Wall::East, Wall::South, Wall::West};

    return walls[static_cast<std::size_t>(dir)];
}

Direction Maze::opposite_direction(const Direction dir)
{
    constexpr std::array directions{Direction::South, Direction::West, Direction::North, Direction::East};

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

    return all_possible_random_directions[static_cast<std::size_t>(random_dist_(random_generator_))];
}

void Maze::clear_walls(const Coords& from, const Coords& to, Direction dir)
{
    const Wall orig_wall = wall_in_direction(dir);
    const Wall dest_wall = wall_in_direction(opposite_direction(dir));

    node(from).clear_wall(orig_wall);
    node(to).clear_wall(dest_wall);
}

class StackNode {
public:
    StackNode(const Coords coords, const std::array<Direction, 4>& dir) : coords_{coords}, check_directions_{dir} { }

    [[nodiscard]] const Coords& coords() const { return coords_; }
    [[nodiscard]] bool has_checked_all_directions() const { return idx_ >= 4; }

    [[nodiscard]] Direction next_direction() { return check_directions_[idx_++]; }

private:
    Coords coords_;
    const std::array<Direction, 4>& check_directions_;
    std::size_t idx_ = 0;
};

void Maze::generate(const Coords& starting_point)
{
    std::vector<StackNode> stack;

    random_generator_.seed(seed_);

    node(starting_point).set_visited();
    stack.emplace_back(starting_point, random_directions());

    while (!stack.empty()) {
        StackNode& current_node = stack.back();

        if (!current_node.has_checked_all_directions()) {
            bool keep_checking = true;

            while (keep_checking && !current_node.has_checked_all_directions()) {
                const auto dir = current_node.next_direction();
                const Coords next_coords = coords_in_direction(current_node.coords(), dir);

                if (valid_coords(next_coords)) {
                    auto& next_node = node(next_coords);

                    if (!next_node.visited()) {
                        clear_walls(current_node.coords(), next_coords, dir);
                        next_node.set_visited();

                        stack.emplace_back(next_coords, random_directions());
                        keep_checking = false;
                    }
                }
            }
        } else {
            stack.pop_back();
        }
    }
}

}  // namespace maze_generator::maze
