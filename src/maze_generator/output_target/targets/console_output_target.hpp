#pragma once

#include <iostream>

#include "../output_target.hpp"

namespace maze_generator::output_target {

class ConsoleOutputTarget : public OutputTarget {
public:
    [[nodiscard]] virtual std::streambuf* streambuf() override { return std::cout.rdbuf(); }
};

}  // namespace maze_generator::output_target
