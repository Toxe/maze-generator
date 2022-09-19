#pragma once

#include <optional>
#include <string>

#include "types.hpp"

namespace maze_generator::command_line {

class CommandLine {
public:
    CommandLine(int argc, char* argv[]);

    [[nodiscard]] int seed() const { return seed_; }
    [[nodiscard]] int zoom() const { return zoom_; }
    [[nodiscard]] bool info() const { return info_; }

    [[nodiscard]] OutputFormat output_format() const { return output_format_; }
    [[nodiscard]] Size size() const { return size_; }

    [[nodiscard]] const std::string& filename() const { return filename_; }

private:
    int seed_ = -1;
    int zoom_ = 1;

    bool info_ = false;

    OutputFormat output_format_;
    Size size_{0, 0};

    std::string filename_;
};

}  // namespace maze_generator::command_line
