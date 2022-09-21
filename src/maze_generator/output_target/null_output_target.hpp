#pragma once

#include "output_target.hpp"

namespace maze_generator::output_target {

class NullStreamBuffer : public std::streambuf {
protected:
    virtual int_type overflow(int_type c) override { return c; }
};

class NullOutputTarget : public OutputTarget {
public:
    [[nodiscard]] virtual std::streambuf* streambuf() override { return &null_stream_buffer_; }

private:
    NullStreamBuffer null_stream_buffer_;
};

}  // namespace maze_generator::output_target
