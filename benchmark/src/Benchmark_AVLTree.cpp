#include <benchmark/benchmark.h>
#include <forest/AVLTree.hpp>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

static void BM_AVLTree_Create_Average_Case(benchmark::State &state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::AVLTree<int, int> AVLTree;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      AVLTree.Insert(dis(gen), 0);
    }
    state.PauseTiming();
    AVLTree.Clear();
    state.ResumeTiming();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::oNLogN);

static void BM_AVLTree_Search_Average_Case(benchmark::State &state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::AVLTree<int, int> AVLTree;
  for (int i = 0; i < state.range(0); ++i) {
    AVLTree.Insert(dis(gen), 0);
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(AVLTree.Search(dis(gen)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Search_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::oLogN);

static void BM_AVLTree_Minimum_Average_Case(benchmark::State &state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::AVLTree<int, int> AVLTree;
  for (int i = 0; i < state.range(0); ++i) {
    AVLTree.Insert(dis(gen), 0);
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(AVLTree.Minimum());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Minimum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::o1);

static void BM_AVLTree_Maximum_Average_Case(benchmark::State &state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::AVLTree<int, int> AVLTree;
  for (int i = 0; i < state.range(0); ++i) {
    AVLTree.Insert(dis(gen), 0);
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(AVLTree.Maximum());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Maximum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::o1);

BENCHMARK_MAIN();