#pragma once

#include <string>

namespace maze_generator::logger {

enum class LogLevel {
    trace,
    debug,
    info,
    warn,
    error,
    critical
};

void log_init(LogLevel log_level);

void log_trace(const std::string& s);
void log_debug(const std::string& s);
void log_info(const std::string& s);
void log_warn(const std::string& s);
void log_error(const std::string& s);
void log_critical(const std::string& s);

struct WithLogLevel {
    explicit WithLogLevel(LogLevel log_level) { log_init(log_level); }
    ~WithLogLevel() { log_init(LogLevel::info); }
};

}  // namespace maze_generator::logger
