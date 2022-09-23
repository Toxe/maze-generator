#pragma once

#include <memory>
#include <ostream>

#include "../maze/maze.hpp"
#include "../output_target/output_target.hpp"
#include "types.hpp"

namespace maze_generator::output_writer {

class OutputWriter {
public:
    explicit OutputWriter(output_target::OutputTarget& output_stream) : out_(output_stream.streambuf()) { }
    virtual ~OutputWriter() = default;

    virtual void output_maze(maze::Maze& maze, int zoom) = 0;

protected:
    void write(const char c)
    {
        out_ << c;
    }

    void write(const unsigned char c)
    {
        out_ << c;
    }

    void write(const char* s)
    {
        out_ << s;
    }

private:
    std::ostream out_;
};

[[nodiscard]] std::unique_ptr<OutputWriter> create_output_writer(output_target::OutputTarget& output_stream, OutputFormat output_format);

}  // namespace maze_generator::output_writer
