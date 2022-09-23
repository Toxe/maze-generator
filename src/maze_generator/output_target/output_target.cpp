#include "output_target.hpp"

#include "targets/console_output_target.hpp"
#include "targets/file_output_target.hpp"
#include "targets/null_output_target.hpp"

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

}  // namespace maze_generator::output_target
