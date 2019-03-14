#include <benchmark/benchmark.h>
#include <forest/QuadTree.hpp>
#include <random>

static void BM_QuadTree_Create_Average_Case(benchmark::State &state) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::QuadTree<double, 10> QuadTree(
      {{0, 0}, {state.range(0) / 2.f, state.range(0) / 2.f}});

  for (auto _ : state) {
    state.PauseTiming();
    QuadTree.clear();
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      QuadTree.insert({dis(gen), dis(gen)});
    }
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QuadTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oNLogN);

static void BM_QuadTree_Search_Average_Case(benchmark::State &state) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::QuadTree<double, 10> QuadTree(
      {{0, 0}, {state.range(0) / 2.f, state.range(0) / 2.f}});

  for (int i = 0; i < state.range(0); ++i) {
    QuadTree.insert({dis(gen), dis(gen)});
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(QuadTree.search({dis(gen), dis(gen)}));
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QuadTree_Search_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oLogN);

static void BM_QuadTree_Query_Average_Case(benchmark::State &state) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::QuadTree<double, 10> QuadTree(
      {{0, 0}, {state.range(0) / 2.f, state.range(0) / 2.f}});

  for (int i = 0; i < state.range(0); ++i) {
    QuadTree.insert({dis(gen), dis(gen)});
  }

  for (auto _ : state) {
    QuadTree.query({{0, 0}, {dis(gen), dis(gen)}}, [](auto point) {});
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_QuadTree_Query_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oN);

BENCHMARK_MAIN();