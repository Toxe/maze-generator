#include "benchmark/benchmark.h"

#include "../maze_generator/maze/generate.hpp"

namespace maze_generator {

constexpr int random_seed = 42;
const Coords starting_point{0, 0};

static void BM_generate(benchmark::State& state)
{
    const Size size{static_cast<int>(state.range(0)), static_cast<int>(state.range(0))};

    for (auto _ : state) {
        auto maze = maze::generate(size, random_seed, starting_point);
        benchmark::DoNotOptimize(maze);
    }
}

BENCHMARK(BM_generate)->RangeMultiplier(4)->Range(1, 1024);

}  // namespace maze_generator
