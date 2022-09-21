#include "catch2/catch_test_macros.hpp"

#include "output_target.hpp"

namespace maze_generator::output_target {

TEST_CASE("output_target::OutputTarget")
{
    SECTION("ConsoloOutputTarget returns a stream buffer")
    {
        auto output_stream = create_output_target("");

        REQUIRE(output_stream != nullptr);
        REQUIRE(output_stream->streambuf() != nullptr);
    }

    SECTION("FileOutputTarget returns a stream buffer")
    {
        auto output_stream = create_output_target("test.txt");

        REQUIRE(output_stream != nullptr);
        REQUIRE(output_stream->streambuf() != nullptr);
    }

    SECTION("NullOutputTarget returns a stream buffer")
    {
        auto output_stream = create_null_output_target();

        REQUIRE(output_stream != nullptr);
        REQUIRE(output_stream->streambuf() != nullptr);
    }
}

}  // namespace maze_generator::output_target
