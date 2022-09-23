#pragma once

#include <fstream>

#include "../output_target.hpp"

namespace maze_generator::output_target {

class FileOutputTarget : public OutputTarget {
public:
    FileOutputTarget(const std::string& filename) { file_.open(filename, std::ofstream::binary); }

    [[nodiscard]] virtual std::streambuf* streambuf() override { return file_.rdbuf(); }

private:
    std::ofstream file_;
};

}  // namespace maze_generator::output_target
