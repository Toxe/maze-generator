#pragma once

#include "output_writer.hpp"

namespace maze_generator::output_writer {

class PrettyOutputWriter : public OutputWriter {
public:
    explicit PrettyOutputWriter(output_target::OutputTarget& output_stream) : OutputWriter(output_stream) { }
};

}  // namespace maze_generator::output_writer
