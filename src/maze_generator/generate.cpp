#include "generate.hpp"

#include <vector>

namespace maze_generator {

struct StackNode {
    const Coords coords;
    const Direction* check_directions;
    int rnd_idx;

    StackNode(const Coords c, const Direction* d) : coords{c}, check_directions{d}, rnd_idx{0} { }
};

std::unique_ptr<maze_generator::Maze> generate(const Size size, const int random_seed, const Coords starting_point)
{
    std::vector<StackNode> stack;

    std::unique_ptr<maze_generator::Maze> maze = std::make_unique<maze_generator::Maze>(size, random_seed);

    maze->set_node_visited(starting_point);
    stack.emplace_back(starting_point, maze->random_directions());

    while (!stack.empty()) {
        StackNode& current_node = stack.back();

        if (current_node.rnd_idx < 4) {
            bool keep_checking = true;

            while (keep_checking && current_node.rnd_idx < 4) {
                const auto dir = current_node.check_directions[current_node.rnd_idx];
                ++current_node.rnd_idx;

                Coords next_coords{maze->coords_in_direction(current_node.coords, dir)};

                if (maze->valid_coords(next_coords) && !maze->node_visited(next_coords)) {
                    maze->clear_walls(current_node.coords, next_coords, dir);
                    maze->set_node_visited(next_coords);

                    stack.emplace_back(next_coords, maze->random_directions());
                    keep_checking = false;
                }
            }
        } else {
            stack.pop_back();
        }
    }

    return maze;
}

}  // namespace maze_generator
