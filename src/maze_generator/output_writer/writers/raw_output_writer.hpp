#pragma once

#include "../output_writer.hpp"

namespace maze_generator::output_writer {

class RawOutputWriter : public OutputWriter {
public:
    RawOutputWriter(output_target::OutputTarget& output_stream, int zoom) : OutputWriter(output_stream), zoom_(zoom) { }

    virtual void output_maze(maze::Maze& maze) override;
    virtual void output_info(const maze::Maze& maze) override;

private:
    int zoom_;
};

}  // namespace maze_generator::output_writer
