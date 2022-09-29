#include "catch2/catch_test_macros.hpp"

#include "../output_target/targets/byte_output_target.hpp"
#include "../output_target/targets/string_output_target.hpp"
#include "output_writer.hpp"

namespace maze_generator::output_writer {

constexpr int test_random_seed = 42;
constexpr maze_generator::Coords test_starting_point{0, 0};

TEST_CASE("output_writer::OutputWriter")
{
    maze_generator::maze::Maze maze({5, 5}, test_random_seed, test_starting_point);

    SECTION("text")
    {
        const char* expected_output = "###########\n"
                                      "#       # #\n"
                                      "####### # #\n"
                                      "#       # #\n"
                                      "# ####### #\n"
                                      "# #   #   #\n"
                                      "# # # ### #\n"
                                      "# # #     #\n"
                                      "# # ##### #\n"
                                      "#   #     #\n"
                                      "###########\n";

        auto output_target = maze_generator::output_target::create_string_output_target();
        auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, OutputFormat::Text);
        output_writer->output_maze(maze, 1);

        CHECK(output_target->str() == expected_output);
    }

    SECTION("data")
    {
        const char* expected_output = "N-SW|N-S-|N-S-|NE--|NE-W\n"
                                      "N--W|N-S-|N-S-|-ES-|-E-W\n"
                                      "-E-W|N--W|NE--|N-SW|-E--\n"
                                      "-E-W|-E-W|--SW|N-S-|-E--\n"
                                      "--SW|-ES-|N-SW|N-S-|-ES-\n";

        auto output_target = maze_generator::output_target::create_string_output_target();
        auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, OutputFormat::Data);
        output_writer->output_maze(maze, 1);

        CHECK(output_target->str() == expected_output);
    }

    SECTION("pretty")
    {
        const char* expected_output = "┌───────────────┬───┐ \n"
                                      "│               │   │ \n"
                                      "├────────────   │   │ \n"
                                      "│               │   │ \n"
                                      "│   ┌───────┬───┘   │ \n"
                                      "│   │       │       │ \n"
                                      "│   │   ╷   └────   │ \n"
                                      "│   │   │           │ \n"
                                      "│   ╵   ├────────   │ \n"
                                      "│       │           │ \n"
                                      "└───────┴───────────┘ \n";

        auto output_target = maze_generator::output_target::create_string_output_target();
        auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, OutputFormat::Pretty);
        output_writer->output_maze(maze, 1);

        CHECK(output_target->str() == expected_output);
    }

    SECTION("raw")
    {
        const std::vector<unsigned char> expected_output = {
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
            0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff,
            0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff,
            0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff,
            0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff,
            0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

        auto output_target = maze_generator::output_target::create_byte_output_target();
        auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, OutputFormat::Raw);
        output_writer->output_maze(maze, 1);

        CHECK(output_target->data() == expected_output);
    }
}

}  // namespace maze_generator::output_writer
