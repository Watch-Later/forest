#include <benchmark/benchmark.h>
#include <forest/BinarySearchTree.hpp>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

class Node : public forest::BinarySearchTreeNodeBase<Node> {
public:
  Node() = default;
  Node(const int &key, const int &value) : mKey(key), mValue(value){};
  ~Node() = default;

public:
  bool operator<(const Node &other) const { return mKey < other.mKey; }
  friend bool operator<(const Node &lhs, const int &rhs);
  friend bool operator<(const int &lhs, const Node &rhs);

public:
  void SetKey(const int &key) { mKey = key; }
  void SetValue(const int &value) { mValue = value; }

public:
  int GetKey() { return mKey; }
  int GetValue() { return mValue; }

private:
  int mKey = 0;
  int mValue = 0;
};

bool operator<(const Node &lhs, const int &rhs) { return lhs.mKey < rhs; }
bool operator<(const int &lhs, const Node &rhs) { return lhs < rhs.mKey; }

static void BM_BinarySearchTree_Create_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (auto _ : state) {
    state.PauseTiming();
    BinarySearchTree.Clear();
    state.ResumeTiming();
    for (int i = a; i < b; ++i) {
      BinarySearchTree.Insert(Node(dis(gen), 0));
    }
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Create_Average_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oNLogN);

static void BM_BinarySearchTree_Create_Worst_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (auto _ : state) {
    state.PauseTiming();
    BinarySearchTree.Clear();
    state.ResumeTiming();
    for (int i = a; i < b; ++i) {
      BinarySearchTree.Insert(Node(i, 0));
    }
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Create_Worst_Case)
    ->RangeMultiplier(2)
    ->Range(1, 1 << 15)
    ->Complexity(benchmark::oNSquared);

static void BM_BinarySearchTree_Search_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = a; i < b; ++i) {
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

static void BM_BinarySearchTree_Search_Worst_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = a; i < b; ++i) {
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

static void BM_BinarySearchTree_Minimum_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = a; i < b; ++i) {
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

static void BM_BinarySearchTree_Maximum_Average_Case(benchmark::State &state) {
  int a = 0;
  int b = static_cast<int>(state.range(0));
  std::uniform_int_distribution<> dis(a, b);
  forest::BinarySearchTree<Node> BinarySearchTree;
  for (int i = a; i < b; ++i) {
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
