#pragma once

#include <string>

#include "../output_writer/output_writer.hpp"
#include "types.hpp"

namespace maze_generator::maze {

class Maze;

void show_info(const Maze& maze, OutputFormat output_format, int zoom);
void output(Maze& maze, OutputFormat output_format, int zoom, output_writer::OutputWriter& out);

}  // namespace maze_generator::maze
