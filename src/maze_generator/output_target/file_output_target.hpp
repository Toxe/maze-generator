#pragma once

#include "output_target.hpp"

#include <fstream>

namespace maze_generator::output_target {

class FileOutputTarget : public OutputTarget {
public:
    FileOutputTarget(const std::string& filename) { file_.open(filename, std::ofstream::binary); }

    [[nodiscard]] virtual std::streambuf* streambuf() override { return file_.rdbuf(); }

private:
    std::ofstream file_;
};

}  // namespace maze_generator::output_target
