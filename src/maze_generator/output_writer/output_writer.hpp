#pragma once

#include <memory>
#include <ostream>

#include "../output_target/output_target.hpp"
#include "types.hpp"

namespace maze_generator::output_writer {

class OutputWriter {
public:
    explicit OutputWriter(output_target::OutputTarget& output_stream) : out_(output_stream.streambuf()) { }

    OutputWriter& operator<<(char c)
    {
        out_ << c;
        return *this;
    }

    OutputWriter& operator<<(unsigned char c)
    {
        out_ << c;
        return *this;
    }

    OutputWriter& operator<<(const char* s)
    {
        out_ << s;
        return *this;
    }

private:
    std::ostream out_;
};

[[nodiscard]] std::unique_ptr<OutputWriter> create_output_writer(output_target::OutputTarget& output_stream, OutputFormat output_format);

}  // namespace maze_generator::output_writer
