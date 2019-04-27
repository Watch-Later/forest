#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>
#include <string>

class Node : public forest::AVLTreeNodeBase<Node> {
public:
  Node() = default;
  Node(const int &key, const std::string &value) : mKey(key), mValue(value){};
  ~Node() = default;

public:
  bool operator<(const Node &other) const { return mKey < other.mKey; }
  friend bool operator<(const Node &lhs, const int &rhs);
  friend bool operator<(const int &lhs, const Node &rhs);

public:
  void SetKey(const int &key) { mKey = key; }
  void SetValue(const std::string &value) { mValue = value; }

public:
  int GetKey() { return mKey; }
  std::string GetValue() { return mValue; }

private:
  int mKey = 0;
  std::string mValue;
};

bool operator<(const Node &lhs, const int &rhs) { return lhs.mKey < rhs; }
bool operator<(const int &lhs, const Node &rhs) { return lhs < rhs.mKey; }

SCENARIO("Test AVL Tree") {
  GIVEN("An empty AVL Tree") {
    forest::AVLTree<Node> AVLTree;
    REQUIRE(AVLTree.Height() == 0);
    REQUIRE(AVLTree.Size() == 0);
    REQUIRE(AVLTree.Minimum() == nullptr);
    REQUIRE(AVLTree.Maximum() == nullptr);
    REQUIRE(AVLTree.Search(GENERATE(-1, 0, 1)) == nullptr);
    WHEN("I insert nodes with keys from 0 up to 9 inclusive") {
      for (int key = 0; key < 10; ++key) {
        AVLTree.Insert(Node(key, ""));
      }
      REQUIRE(AVLTree.Height() == 4);
      REQUIRE(AVLTree.Size() == 10);
      AND_WHEN("I want the node with the minimum key") {
        auto min = AVLTree.Minimum();
        THEN("This node exists") {
          REQUIRE(min != nullptr);
          CHECK(min->GetKey() == 0);
          CHECK(min->GetValue() == "");
        }
      }
      AND_WHEN("I want the node with the maximum key") {
        auto max = AVLTree.Maximum();
        THEN("This node exists") {
          REQUIRE(max != nullptr);
          CHECK(max->GetKey() == 9);
          CHECK(max->GetValue() == "");
        }
      }
      AND_WHEN("I search for a node with a key that doesn't exist") {
        int key = GENERATE(-1, 10);
        auto result = AVLTree.Search(key);
        THEN("This node doesn't exist") { REQUIRE(result == nullptr); }
      }
      AND_WHEN("I search for a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        auto result = AVLTree.Search(key);
        THEN("This node exists") {
          REQUIRE(result != nullptr);
          CHECK(result->GetKey() == key);
          CHECK(result->GetValue() == "");
        }
      }
      AND_WHEN("I remove a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        AVLTree.Remove(key);
        THEN("This node is successfully removed") {
          REQUIRE(AVLTree.Search(key) == nullptr);
          CHECK(AVLTree.Height() == 4);
          CHECK(AVLTree.Size() == 9);
        }
      }
      AND_WHEN("I clear the AVL Tree") {
        AVLTree.Clear();
        THEN("The height and the size of the AVL Tree change") {
          REQUIRE(AVLTree.Height() == 0);
          REQUIRE(AVLTree.Size() == 0);
        }
      }
    }
  }
}
