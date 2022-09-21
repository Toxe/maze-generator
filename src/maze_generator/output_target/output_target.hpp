#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace maze_generator::output_target {

class OutputTarget {
public:
    virtual ~OutputTarget() = default;

    [[nodiscard]] virtual std::streambuf* streambuf() = 0;
};

[[nodiscard]] std::unique_ptr<OutputTarget> create_output_target(const std::string& filename);
[[nodiscard]] std::unique_ptr<OutputTarget> create_null_output_target();

}  // namespace maze_generator::output_target
