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
    virtual void output_info(const maze::Maze& maze, int zoom);

protected:
    void write(char c);
    void write(char c, int repeat);
    void write(unsigned char c);
    void write(unsigned char c, int repeat);
    void write(const char* s);

private:
    std::ostream out_;
};

[[nodiscard]] std::unique_ptr<OutputWriter> create_output_writer(output_target::OutputTarget& output_stream, OutputFormat output_format);

}  // namespace maze_generator::output_writer
