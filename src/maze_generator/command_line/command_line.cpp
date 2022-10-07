#include "command_line.hpp"

#include <cstdlib>
#include <optional>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "fmt/core.h"

#include "../logger/logger.hpp"

namespace maze_generator::command_line {

[[noreturn]] void show_usage_and_exit(const CLI::App& app, const char* error_message = nullptr, const std::optional<CLI::ParseError>& error = {})
{
    if (error_message)
        fmt::print("\n{}\n", error_message);

    std::exit(error ? app.exit(error.value()) : 0);
}

CommandLine::CommandLine(std::span<const char*> args)
{
    const char* description = "Maze Generator";
    int log_level_flag = 0;
    bool format_text = false;
    bool format_pretty = false;
    bool format_data = false;
    bool format_raw = false;

    CLI::App app{description};
    app.add_option("width", size_.width, fmt::format("maze width (default: {})", size_.width));
    app.add_option("height", size_.height, fmt::format("maze height (default: {})", size_.height));
    app.add_option("filename", filename_, "output filename");
    app.add_option("-s,--seed", seed_, "random seed (0 or bigger)");
    app.add_option("-z,--zoom", zoom_, fmt::format("pixel zoom factor for .raw files (default: {})", zoom_));
    app.add_flag("-i,--info", info_, fmt::format("output additional info (default: {})", info_));
    app.add_flag("-v", log_level_flag, "log level (-v: INFO, -vv: DEBUG, -vvv: TRACE)");

    auto* grp_output = app.add_option_group("output format (default: text)");
    auto* flag1 = grp_output->add_flag("-t,--text", format_text, "text: uses ASCII '#' characters for walls");
    auto* flag2 = grp_output->add_flag("-p,--pretty", format_pretty, "pretty: uses UNICODE line drawing characters")->excludes(flag1);
    auto* flag3 = grp_output->add_flag("-d,--data", format_data, "data: export the internal wall data")->excludes(flag1, flag2);
    grp_output->add_flag("-r,--raw", format_raw, "raw: generate a 1 byte per pixel grayscale raw image")->excludes(flag1, flag2, flag3);

    try {
        app.parse(static_cast<int>(args.size()), args.data());
    } catch (const CLI::ParseError& error) {
        show_usage_and_exit(app, nullptr, error);
    }

    logger::LogLevel log_level = logger::LogLevel::warn;

    switch (log_level_flag) {
        case 1: log_level = logger::LogLevel::info; break;
        case 2: log_level = logger::LogLevel::debug; break;
        case 3: log_level = logger::LogLevel::trace; break;
        default:
            log_level = logger::LogLevel::warn;
    }

    logger::log_init(log_level);
    logger::log_debug(fmt::format("command line option width: {}", size_.width));
    logger::log_debug(fmt::format("command line option height: {}", size_.height));
    logger::log_debug(fmt::format("command line option filename: {}", filename_));
    logger::log_debug(fmt::format("command line option --text: {}", format_text));
    logger::log_debug(fmt::format("command line option --pretty: {}", format_pretty));
    logger::log_debug(fmt::format("command line option --data: {}", format_data));
    logger::log_debug(fmt::format("command line option --raw: {}", format_raw));
    logger::log_debug(fmt::format("command line option --seed: {}", seed_));
    logger::log_debug(fmt::format("command line option --zoom: {}", zoom_));
    logger::log_debug(fmt::format("command line option --info: {}", info_));

    if (size_.width < 1 || size_.height < 1)
        show_usage_and_exit(app, "Error: Maze width and height need to be at least 1");

    if (zoom_ < 1)
        zoom_ = 1;

    output_format_ = OutputFormat::Text;

    if (format_pretty)
        output_format_ = OutputFormat::Pretty;
    else if (format_data)
        output_format_ = OutputFormat::Data;
    else if (format_raw)
        output_format_ = OutputFormat::Raw;
}

}  // namespace maze_generator::command_line
