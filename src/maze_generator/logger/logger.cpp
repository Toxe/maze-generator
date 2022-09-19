#include "logger.hpp"

#include "spdlog/spdlog.h"

namespace maze_generator::logger {

void log_init(LogLevel log_level)
{
    spdlog::level::level_enum spdlog_log_level = spdlog::level::warn;

    switch (log_level) {
        case LogLevel::trace: spdlog_log_level = spdlog::level::trace; break;
        case LogLevel::debug: spdlog_log_level = spdlog::level::debug; break;
        case LogLevel::info: spdlog_log_level = spdlog::level::info; break;
        case LogLevel::warn: spdlog_log_level = spdlog::level::warn; break;
        case LogLevel::error: spdlog_log_level = spdlog::level::err; break;
        case LogLevel::critical: spdlog_log_level = spdlog::level::critical; break;
    }

    spdlog::set_level(spdlog_log_level);
}

void log_trace(const std::string& s)
{
    spdlog::trace(s);
}

void log_debug(const std::string& s)
{
    spdlog::debug(s);
}

void log_info(const std::string& s)
{
    spdlog::info(s);
}

void log_warn(const std::string& s)
{
    spdlog::warn(s);
}

void log_error(const std::string& s)
{
    spdlog::error(s);
}

void log_critical(const std::string& s)
{
    spdlog::critical(s);
}

}  // namespace maze_generator::logger
