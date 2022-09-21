#include "benchmark/benchmark.h"

#include "../maze_generator/maze/generate.hpp"
#include "../maze_generator/maze/output.hpp"

namespace maze_generator {

constexpr int random_seed = 42;
const Coords starting_point{0, 0};

static void BM_output(benchmark::State& state, OutputFormat output_format, int zoom)
{
    const Size size{static_cast<int>(state.range(0)), static_cast<int>(state.range(0))};
    const auto maze = maze::generate(size, random_seed, starting_point);

    auto output_target = maze_generator::output_target::create_null_output_target();
    auto output_writer = maze_generator::output_writer::create_output_writer(*output_target, output_format);

    for (auto _ : state)
        maze::output(*maze, output_format, zoom, *output_writer);
}

BENCHMARK_CAPTURE(BM_output, text, OutputFormat::Text, 1)->RangeMultiplier(4)->Range(1, 1024);
BENCHMARK_CAPTURE(BM_output, pretty, OutputFormat::Pretty, 1)->RangeMultiplier(4)->Range(1, 1024);
BENCHMARK_CAPTURE(BM_output, data, OutputFormat::Data, 1)->RangeMultiplier(4)->Range(1, 1024);
BENCHMARK_CAPTURE(BM_output, raw_zoom_1, OutputFormat::Raw, 1)->RangeMultiplier(4)->Range(1, 1024);
BENCHMARK_CAPTURE(BM_output, raw_zoom_10, OutputFormat::Raw, 10)->RangeMultiplier(4)->Range(1, 1024);

}  // namespace maze_generator