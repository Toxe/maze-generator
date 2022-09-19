#pragma once

#include <memory>

#include "maze.hpp"
#include "types.hpp"

namespace maze_generator {

std::unique_ptr<maze_generator::Maze> generate(Size size, int random_seed, Coords starting_point);

}  // namespace maze_generator
