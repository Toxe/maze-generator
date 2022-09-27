#pragma once

#include <memory>
#include <streambuf>
#include <string>

namespace maze_generator::output_target {

class ByteOutputTarget;
class StringOutputTarget;

class OutputTarget {
public:
    virtual ~OutputTarget() = default;

    [[nodiscard]] virtual std::streambuf* streambuf() = 0;
};

[[nodiscard]] std::unique_ptr<OutputTarget> create_output_target(const std::string& filename);
[[nodiscard]] std::unique_ptr<OutputTarget> create_null_output_target();
[[nodiscard]] std::unique_ptr<ByteOutputTarget> create_byte_output_target();
[[nodiscard]] std::unique_ptr<StringOutputTarget> create_string_output_target();

}  // namespace maze_generator::output_target
