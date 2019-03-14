#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/BinarySearchTree.hpp>

class Node : public forest::BinarySearchTreeNodeBase<Node> {
 public:
  Node() = default;
  Node(const int& KEY, const std::string& VALUE) : key(KEY), value(VALUE){};
  ~Node() = default;

 public:
  bool operator<(const Node& other) const { return this->key < other.key; }

 public:
  void SetKey(int KEY) { key = KEY; }
  void SetValue(std::string VALUE) { value = VALUE; }

 public:
  int GetKey() { return key; }
  std::string GetValue() { return value; }

 public:
  friend bool operator<(const Node& lhs, int rhs);
  friend bool operator<(int lhs, const Node& rhs);

 private:
  int key;
  std::string value;
};

bool operator<(const Node& lhs, int rhs) { return lhs.key < rhs; }
bool operator<(int lhs, const Node& rhs) { return lhs < rhs.key; }

SCENARIO("Test Binary Search Tree") {
  GIVEN("A Binary Search Tree") {
    forest::BinarySearchTree<Node> BinarySearchTree;
    WHEN("The Binary Search Tree is empty") {
      THEN("Test Height()") { REQUIRE(BinarySearchTree.Height() == 0); }
      THEN("Test Size()") { REQUIRE(BinarySearchTree.Size() == 0); }
      THEN("Test Maximum()") { REQUIRE(BinarySearchTree.Maximum() == nullptr); }
      THEN("Test Minimum()") { REQUIRE(BinarySearchTree.Minimum() == nullptr); }
      THEN("Test Search(555)") {
        REQUIRE(BinarySearchTree.Search(555) == nullptr);
      }
      THEN("Test Clear()") {
        BinarySearchTree.Clear();
        REQUIRE(BinarySearchTree.Height() == 0);
        REQUIRE(BinarySearchTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in random order") {
      BinarySearchTree.Insert(Node(4, ""));
      BinarySearchTree.Insert(Node(2, ""));
      BinarySearchTree.Insert(Node(90, ""));
      BinarySearchTree.Insert(Node(3, ""));
      BinarySearchTree.Insert(Node(0, ""));
      BinarySearchTree.Insert(Node(14, ""));
      BinarySearchTree.Insert(Node(45, ""));
      THEN("Test Height()") { REQUIRE(BinarySearchTree.Height() == 4); }
      THEN("Test Size()") { REQUIRE(BinarySearchTree.Size() == 7); }
      THEN("Test Maximum()") {
        auto max = BinarySearchTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->GetKey() == 90);
      }
      THEN("Test Minimum()") {
        auto min = BinarySearchTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->GetKey() == 0);
      }
      THEN("Test Search(1337)") {
        REQUIRE(BinarySearchTree.Search(1337) == nullptr);
      }
      THEN("Test Search(3)") {
        auto result = BinarySearchTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->GetKey() == 3);
      }
      THEN("Test Remove(45)") {
        BinarySearchTree.Remove(45);
        REQUIRE(BinarySearchTree.Search(45) == nullptr);
        REQUIRE(BinarySearchTree.Height() == 3);
        REQUIRE(BinarySearchTree.Size() == 6);
      }
      THEN("Test Clear()") {
        BinarySearchTree.Clear();
        REQUIRE(BinarySearchTree.Height() == 0);
        REQUIRE(BinarySearchTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; ++i) {
        BinarySearchTree.Insert(Node(i, ""));
      }
      THEN("Test Height()") { REQUIRE(BinarySearchTree.Height() == 10); }
      THEN("Test Size()") { REQUIRE(BinarySearchTree.Size() == 10); }
      THEN("Test Maximum()") {
        auto max = BinarySearchTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->GetKey() == 9);
      }
      THEN("Test Minimum()") {
        auto min = BinarySearchTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->GetKey() == 0);
      }
      THEN("Test Search(1337)") {
        REQUIRE(BinarySearchTree.Search(1337) == nullptr);
      }
      THEN("Test Search(3)") {
        auto result = BinarySearchTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->GetKey() == 3);
      }
      THEN("Test Remove(0)") {
        BinarySearchTree.Remove(0);
        REQUIRE(BinarySearchTree.Search(0) == nullptr);
        REQUIRE(BinarySearchTree.Height() == 9);
        REQUIRE(BinarySearchTree.Size() == 9);
      }
      THEN("Test Clear()") {
        BinarySearchTree.Clear();
        REQUIRE(BinarySearchTree.Height() == 0);
        REQUIRE(BinarySearchTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; --i) {
        BinarySearchTree.Insert(Node(i, ""));
      }
      THEN("Test Height()") { REQUIRE(BinarySearchTree.Height() == 10); }
      THEN("Test Size()") { REQUIRE(BinarySearchTree.Size() == 10); }
      THEN("Test Maximum()") {
        auto max = BinarySearchTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->GetKey() == 9);
      }
      THEN("Test Minimum()") {
        auto min = BinarySearchTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->GetKey() == 0);
      }
      THEN("Test Search(1337)") {
        REQUIRE(BinarySearchTree.Search(1337) == nullptr);
      }
      THEN("Test Search(3)") {
        auto result = BinarySearchTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->GetKey() == 3);
      }
      THEN("Test Remove(0)") {
        BinarySearchTree.Remove(0);
        REQUIRE(BinarySearchTree.Search(0) == nullptr);
        REQUIRE(BinarySearchTree.Height() == 9);
        REQUIRE(BinarySearchTree.Size() == 9);
      }
      THEN("Test Clear()") {
        BinarySearchTree.Clear();
        REQUIRE(BinarySearchTree.Height() == 0);
        REQUIRE(BinarySearchTree.Size() == 0);
      }
    }
  }
}
