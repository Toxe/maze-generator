#include <cstdlib>
#include <filesystem>
#include <optional>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include "cli.hpp"

void show_usage_and_exit(const CLI::App& app, const char* error_message = nullptr, const std::optional<CLI::ParseError>& error = {})
{
    if (error_message)
        fmt::print("\n{}\n", error_message);

    std::exit(error ? app.exit(error.value()) : 0);
}

std::tuple<int, int, int, std::string, OutputFormat, int, bool> eval_args(int argc, char* argv[])
{
    const auto progname{std::filesystem::path{argv[0]}.filename().string()};
    const auto description = "Maze Generator";
    int log_level_flag = 0;
    int seed = -1;
    int zoom = 1;
    int width, height;
    bool info = false;
    bool format_text = false;
    bool format_pretty = false;
    bool format_data = false;
    bool format_raw = false;
    std::string filename;

    CLI::App app{description};

    app.add_option("width", width, "maze width")->required();
    app.add_option("height", height, "maze height")->required();
    app.add_option("filename", filename, "output filename");
    app.add_option("-s,--seed", seed, "random seed (0 or bigger)");
    app.add_option("-z,--zoom", zoom, "pixel zoom factor for .raw files");
    app.add_flag("-i,--info", info, "output additional info");
    app.add_flag("-v", log_level_flag, "log level (-v: verbose, -vv: debug messages)");

    auto grp_output = app.add_option_group("output format (default: text)");
    const auto f1 = grp_output->add_flag("-t,--text", format_text, "text: uses ASCII '#' characters for walls");
    const auto f2 = grp_output->add_flag("-p,--pretty", format_pretty, "pretty: uses UNICODE line drawing characters")->excludes(f1);
    const auto f3 = grp_output->add_flag("-d,--data", format_data, "data: export the internal wall data")->excludes(f1, f2);
    grp_output->add_flag("-r,--raw", format_raw, "raw: generate a 1 byte per pixel grayscale raw image")->excludes(f1, f2, f3);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& error) {
        show_usage_and_exit(app, nullptr, error);
    }

    auto log_level = (log_level_flag >= 1) ? spdlog::level::info : spdlog::level::warn;

    if (log_level_flag >= 2)
        log_level = spdlog::level::debug;

    spdlog::set_level(log_level);
    spdlog::debug("command line option \"width\": {}", width);
    spdlog::debug("command line option \"height\": {}", height);
    spdlog::debug("command line option \"filename\": \"{}\"", filename);
    spdlog::debug("command line option --text: {}", format_text);
    spdlog::debug("command line option --pretty: {}", format_pretty);
    spdlog::debug("command line option --data: {}", format_data);
    spdlog::debug("command line option --raw: {}", format_raw);
    spdlog::debug("command line option --seed: {}", seed);
    spdlog::debug("command line option --zoom: {}", zoom);
    spdlog::debug("command line option --info: {}", info);

    if (width < 1 || height < 1)
        show_usage_and_exit(app, "Error: Maze width and height need to be at least 1");

    if (zoom < 1)
        zoom = 1;

    OutputFormat output_format = OutputFormat::Text;

    if (format_pretty)
        output_format = OutputFormat::Pretty;
    else if (format_data)
        output_format = OutputFormat::Data;
    else if (format_raw)
        output_format = OutputFormat::Raw;

    return std::make_tuple(seed, width, height, filename, output_format, zoom, info);
}
