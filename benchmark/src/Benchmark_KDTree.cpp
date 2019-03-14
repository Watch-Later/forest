#include <benchmark/benchmark.h>
#include <forest/KDTree.hpp>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

static void BM_KDTree_Create_Average_Case(benchmark::State &state) {
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::KDTree<double, 2>::Points points;
  forest::KDTree<double, 2> KDTree;

  for (auto _ : state) {
    state.PauseTiming();
    points.clear();
    for (double i = 0; i < state.range(0); ++i) {
      points.push_back({dis(gen), dis(gen)});
    }
    state.ResumeTiming();

    KDTree.fill(points.begin(), points.end());

    state.PauseTiming();
    KDTree.clear();
    state.ResumeTiming();
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oNLogN);

static void BM_KDTree_Search_Average_Case(benchmark::State &state) {
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::KDTree<double, 2>::Points points;
  for (double i = 0; i < state.range(0); ++i) {
    points.push_back({dis(gen), dis(gen)});
  }

  forest::KDTree<double, 2> KDTree(points.begin(), points.end());

  for (auto _ : state) {
    benchmark::DoNotOptimize(KDTree.search({dis(gen), dis(gen)}));
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Search_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oLogN);

static void BM_KDTree_Minimum_Average_Case(benchmark::State &state) {
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::KDTree<double, 2>::Points points;
  for (double i = 0; i < state.range(0); ++i) {
    points.push_back({dis(gen), dis(gen)});
  }

  forest::KDTree<double, 2> KDTree(points.begin(), points.end());

  for (auto _ : state) {
    benchmark::DoNotOptimize(KDTree.minimum(0));
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Minimum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity([](auto n) -> double { return std::sqrt(n); });

static void BM_KDTree_Maximum_Average_Case(benchmark::State &state) {
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::KDTree<double, 2>::Points points;
  for (double i = 0; i < state.range(0); ++i) {
    points.push_back({dis(gen), dis(gen)});
  }

  forest::KDTree<double, 2> KDTree(points.begin(), points.end());

  for (auto _ : state) {
    benchmark::DoNotOptimize(KDTree.maximum(0));
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Maximum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity([](auto n) -> double { return std::sqrt(n); });

static void BM_KDTree_Query_Average_Case(benchmark::State &state) {
  std::uniform_real_distribution<> dis(-state.range(0) / 2.f,
                                       state.range(0) / 2.f);

  forest::KDTree<double, 2>::Points points;
  for (double i = 0; i < state.range(0); ++i) {
    points.push_back({dis(gen), dis(gen)});
  }

  forest::KDTree<double, 2> KDTree(points.begin(), points.end());

  for (auto _ : state) {
    KDTree.query({{0, 0}, {dis(gen), dis(gen)}}, [](auto point) {});
  }

  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Query_Average_Case)
    ->RangeMultiplier(2)
    ->Range(2, 1 << 20)
    ->Complexity(benchmark::oN);

BENCHMARK_MAIN();