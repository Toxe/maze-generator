#pragma once

#include "output_writer.hpp"

namespace maze_generator::output_writer {

class RawOutputWriter : public OutputWriter {
public:
    explicit RawOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }
};

}  // namespace maze_generator::output_writer
