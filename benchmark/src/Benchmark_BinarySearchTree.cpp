#include <benchmark/benchmark.h>
#include <forest/BinarySearchTree.hpp>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

class Node : public forest::BinarySearchTreeNodeBase<Node> {
 public:
  Node() = default;
  Node(const int& KEY, const int& VALUE) : key(KEY), value(VALUE){};
  ~Node() = default;

 public:
  bool operator<(const Node& other) const { return this->key < other.key; }
  friend bool operator<(const Node& lhs, int rhs);
  friend bool operator<(int lhs, const Node& rhs);

 public:
  void SetKey(int KEY) { key = KEY; }
  void SetValue(int VALUE) { value = VALUE; }

 public:
  int GetKey() { return key; }
  int GetValue() { return value; }

 private:
  int key;
  int value;
};

bool operator<(const Node& lhs, int rhs) { return lhs.key < rhs; }
bool operator<(int lhs, const Node& rhs) { return lhs < rhs.key; }

static void BM_BinarySearchTree_Create_Average_Case(benchmark::State& state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (auto _ : state) {
    state.PauseTiming();
    BinarySearchTree.Clear();
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      BinarySearchTree.Insert(Node(dis(gen), 0));
    }
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oNLogN);

static void BM_BinarySearchTree_Create_Worst_Case(benchmark::State& state) {
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (auto _ : state) {
    state.PauseTiming();
    BinarySearchTree.Clear();
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      BinarySearchTree.Insert(Node(i, 0));
    }
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Create_Worst_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oNSquared);

static void BM_BinarySearchTree_Search_Average_Case(benchmark::State& state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = 0; i < state.range(0); ++i) {
    BinarySearchTree.Insert(Node(dis(gen), 0));
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(BinarySearchTree.Search(dis(gen)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Search_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oLogN);

static void BM_BinarySearchTree_Search_Worst_Case(benchmark::State& state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = 0; i < state.range(0); ++i) {
    BinarySearchTree.Insert(Node(i, 0));
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(BinarySearchTree.Search(dis(gen)));
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Search_Worst_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oN);

static void BM_BinarySearchTree_Minimum_Average_Case(benchmark::State& state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = 0; i < state.range(0); ++i) {
    BinarySearchTree.Insert(Node(dis(gen), 0));
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(BinarySearchTree.Minimum());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Minimum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::o1);

static void BM_BinarySearchTree_Maximum_Average_Case(benchmark::State& state) {
  std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = 0; i < state.range(0); ++i) {
    BinarySearchTree.Insert(Node(dis(gen), 0));
  }
  for (auto _ : state) {
    benchmark::DoNotOptimize(BinarySearchTree.Maximum());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Maximum_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::o1);

BENCHMARK_MAIN();