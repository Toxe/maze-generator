#include "output_target.hpp"

#include "targets/byte_output_target.hpp"
#include "targets/console_output_target.hpp"
#include "targets/file_output_target.hpp"
#include "targets/null_output_target.hpp"
#include "targets/string_output_target.hpp"

namespace maze_generator::output_target {

std::unique_ptr<OutputTarget> create_output_target(const std::string& filename)
{
    if (filename.empty())
        return std::make_unique<ConsoleOutputTarget>();
    else
        return std::make_unique<FileOutputTarget>(filename);
}

std::unique_ptr<OutputTarget> create_null_output_target()
{
    return std::make_unique<NullOutputTarget>();
}

std::unique_ptr<ByteOutputTarget> create_byte_output_target()
{
    return std::make_unique<ByteOutputTarget>();
}

std::unique_ptr<StringOutputTarget> create_string_output_target()
{
    return std::make_unique<StringOutputTarget>();
}

}  // namespace maze_generator::output_target
