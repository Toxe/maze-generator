#pragma once

#include <string>
#include <tuple>

enum class OutputFormat { Text, Raw, Pretty, Data };

std::tuple<int, int, int, std::string, OutputFormat, int, bool> eval_args(int argc, char* argv[]);
