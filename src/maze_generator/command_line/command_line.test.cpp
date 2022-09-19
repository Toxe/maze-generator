#include "catch2/catch_test_macros.hpp"

#include <array>

#include "command_line.hpp"

namespace maze_generator::command_line {

TEST_CASE("command_line::CommandLine")
{
    SECTION("default width and height is 10/10")
    {
        auto args = std::to_array({"maze_generator"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.size().width == 10);
        CHECK(cli.size().height == 10);
    }

    SECTION("can set width and height")
    {
        auto args = std::to_array({"maze_generator", "20", "30"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.size().width == 20);
        CHECK(cli.size().height == 30);
    }

    SECTION("can set filename")
    {
        auto args = std::to_array({"maze_generator", "10", "10", "output.raw"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.filename() == args[3]);
    }

    SECTION("default zoom is 1")
    {
        auto args = std::to_array({"maze_generator"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.zoom() == 1);
    }

    SECTION("can set zoom with -z")
    {
        auto args = std::to_array({"maze_generator", "-z", "3"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.zoom() == 3);
    }

    SECTION("can set zoom with --zoom")
    {
        auto args = std::to_array({"maze_generator", "--zoom", "3"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.zoom() == 3);
    }

    SECTION("can set seed with -s")
    {
        auto args = std::to_array({"maze_generator", "-s", "5"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.seed() == 5);
    }

    SECTION("can set seed with --seed")
    {
        auto args = std::to_array({"maze_generator", "--seed", "5"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.seed() == 5);
    }

    SECTION("default info flag is false")
    {
        auto args = std::to_array({"maze_generator"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.info() == false);
    }

    SECTION("can show info with -i")
    {
        auto args = std::to_array({"maze_generator", "-i"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.info() == true);
    }

    SECTION("can show info with --info")
    {
        auto args = std::to_array({"maze_generator", "--info"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.info() == true);
    }

    SECTION("default output format is text")
    {
        auto args = std::to_array({"maze_generator"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Text);
    }

    SECTION("can change output format to text with -t")
    {
        auto args = std::to_array({"maze_generator", "-t"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Text);
    }

    SECTION("can change output format to text with --text")
    {
        auto args = std::to_array({"maze_generator", "--text"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Text);
    }

    SECTION("can change output format to raw with -r")
    {
        auto args = std::to_array({"maze_generator", "-r"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Raw);
    }

    SECTION("can change output format to raw with --raw")
    {
        auto args = std::to_array({"maze_generator", "--raw"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Raw);
    }

    SECTION("can change output format to pretty with -p")
    {
        auto args = std::to_array({"maze_generator", "-p"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Pretty);
    }

    SECTION("can change output format to pretty with --pretty")
    {
        auto args = std::to_array({"maze_generator", "--pretty"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Pretty);
    }

    SECTION("can change output format to data with -d")
    {
        auto args = std::to_array({"maze_generator", "-d"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Data);
    }

    SECTION("can change output format to data with --data")
    {
        auto args = std::to_array({"maze_generator", "--data"});
        const CommandLine cli(static_cast<int>(args.size()), args.data());

        CHECK(cli.output_format() == OutputFormat::Data);
    }
}

}  // namespace maze_generator::command_line
