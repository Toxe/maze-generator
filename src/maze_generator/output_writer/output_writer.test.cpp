#include "catch2/catch_test_macros.hpp"

#include "output_writer.hpp"

namespace maze_generator::output_writer {

TEST_CASE("output_writer::OutputWriter")
{
    auto output_stream = output_target::create_null_output_target();

    SECTION("can create TextOutputWriter")
    {
        auto output_writer = create_output_writer(*output_stream, maze_generator::OutputFormat::Text);

        CHECK(output_writer != nullptr);
    }

    SECTION("can create RawOutputWriter")
    {
        auto output_writer = create_output_writer(*output_stream, maze_generator::OutputFormat::Raw);

        CHECK(output_writer != nullptr);
    }

    SECTION("can create PrettyOutputWriter")
    {
        auto output_writer = create_output_writer(*output_stream, maze_generator::OutputFormat::Pretty);

        CHECK(output_writer != nullptr);
    }

    SECTION("can create DataOutputWriter")
    {
        auto output_writer = create_output_writer(*output_stream, maze_generator::OutputFormat::Data);

        CHECK(output_writer != nullptr);
    }
}

}  // namespace maze_generator::output_writer
