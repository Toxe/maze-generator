#pragma once

namespace maze_generator {

enum class OutputFormat {
    Text,
    Raw,
    Pretty,
    Data
};

struct Size {
    int width = 0;
    int height = 0;
};

}  // namespace maze_generator
