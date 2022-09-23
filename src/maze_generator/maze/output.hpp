#pragma once

#include <string>

#include "../output_writer/output_writer.hpp"
#include "types.hpp"

namespace maze_generator::maze {

class Maze;

void show_info(const Maze& maze, OutputFormat output_format, int zoom);

}  // namespace maze_generator::maze
