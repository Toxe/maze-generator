#pragma once

#include <cassert>
#include <limits>
#include <vector>

#include "../output_target.hpp"

namespace maze_generator::output_target {

class ByteStreamBuffer : public std::streambuf {
public:
    [[nodiscard]] const std::vector<unsigned char>& buf() const { return buf_; }

protected:
    virtual int_type overflow(int_type c) override
    {
        assert(c >= std::numeric_limits<unsigned char>::min());
        assert(c <= std::numeric_limits<unsigned char>::max());

        buf_.push_back(static_cast<unsigned char>(c));
        return c;
    }

private:
    std::vector<unsigned char> buf_;
};

class ByteOutputTarget : public OutputTarget {
public:
    [[nodiscard]] virtual std::streambuf* streambuf() override { return &byte_stream_buffer_; }
    [[nodiscard]] const std::vector<unsigned char>& data() const { return byte_stream_buffer_.buf(); }

private:
    ByteStreamBuffer byte_stream_buffer_;
};

}  // namespace maze_generator::output_target
