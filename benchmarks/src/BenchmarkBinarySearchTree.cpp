#include <benchmark/benchmark.h>
#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

static void BM_BinarySearchTree_Create_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<int> tree;
  for (auto _ : state) {
    for (int i = a; i < b; ++i) {
      tree.insert(dis(gen));
    }
    tree.clear();
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::oNLogN);

static void BM_BinarySearchTree_Search_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<int> tree;
  for (int i = a; i < b; ++i) {
    tree.insert(dis(gen));
  }
  for (auto _ : state) {
    tree.search(dis(gen));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Search_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 20)
    ->Complexity(benchmark::oLogN);

BENCHMARK_MAIN();
