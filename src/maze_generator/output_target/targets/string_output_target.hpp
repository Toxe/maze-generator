#pragma once

#include <sstream>
#include <string>

#include "../output_target.hpp"

namespace maze_generator::output_target {

class StringOutputTarget : public OutputTarget {
public:
    [[nodiscard]] virtual std::streambuf* streambuf() override { return sstream_.rdbuf(); }
    [[nodiscard]] std::string str() const { return sstream_.str(); }

private:
    std::stringstream sstream_;
};

}  // namespace maze_generator::output_target
