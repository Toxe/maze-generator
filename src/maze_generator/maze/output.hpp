#pragma once

#include <string>

#include "types.hpp"

namespace maze_generator::maze {

class Maze;

void output(Maze* maze, const std::string& filename, OutputFormat output_format, int zoom, bool show_info);

}  // namespace maze_generator::maze
