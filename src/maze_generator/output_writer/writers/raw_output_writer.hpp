#pragma once

#include "../output_writer.hpp"

namespace maze_generator::output_writer {

class RawOutputWriter : public OutputWriter {
public:
    explicit RawOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }

    virtual void output_maze(maze::Maze& maze, int zoom) override;
    virtual void output_info(const maze::Maze& maze, int zoom) override;
};

}  // namespace maze_generator::output_writer
