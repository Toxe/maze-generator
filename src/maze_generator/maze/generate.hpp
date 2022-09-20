#pragma once

#include <memory>

#include "maze.hpp"
#include "types.hpp"

namespace maze_generator::maze {

std::unique_ptr<maze_generator::maze::Maze> generate(Size size, int random_seed, Coords starting_point);

}  // namespace maze_generator::maze
