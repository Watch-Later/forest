#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

//////////
// Node //
//////////

class Node : public forest::BinarySearchTreeNodeBase<Node> {
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

int main() {
  forest::BinarySearchTree<Node> BinarySearchTree;

  ////////////
  // Insert //
  ////////////

  BinarySearchTree.Insert(Node(2, "Thor"));
  BinarySearchTree.Insert(Node(4, "Odin"));
  BinarySearchTree.Insert(Node(90, "Loki"));
  BinarySearchTree.Insert(Node(3, "Baldr"));
  BinarySearchTree.Insert(Node(0, "Frigg"));
  BinarySearchTree.Insert(Node(14, "Eir"));
  BinarySearchTree.Insert(Node(45, "Heimdall"));

  /////////////////////////
  // Pre Order Traversal //
  /////////////////////////

  std::cout << "PreOrderTraversal()";
  std::cout << " = ";
  BinarySearchTree.PreOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  ////////////////////////
  // In Order Traversal //
  ////////////////////////

  std::cout << "InOrderTraversal()";
  std::cout << " = ";
  BinarySearchTree.InOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  //////////////////////////
  // Post Order Traversal //
  //////////////////////////

  std::cout << "PostOrderTraversal()";
  std::cout << " = ";
  BinarySearchTree.PostOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  /////////////////////////////
  // Breadth First Traversal //
  /////////////////////////////

  std::cout << "BreadthFirstTraversal()";
  std::cout << " = ";
  BinarySearchTree.BreadthFirstTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  ////////////
  // Remove //
  ////////////

  BinarySearchTree.Remove(3);
  std::cout << "Remove(3)" << std::endl;

  ////////////
  // Search //
  ////////////

  auto result = BinarySearchTree.Search(3);
  std::cout << "Search(3)";
  std::cout << " = ";
  if (result) {
    std::cout << "Found" << std::endl;
  } else {
    std::cout << "Not Found" << std::endl;
  }

  /////////////
  // Minimum //
  /////////////

  auto min = BinarySearchTree.Minimum();
  std::cout << "Minimum()";
  std::cout << " = ";
  if (min) {
    std::cout << min->GetKey() << std::endl;
  }

  /////////////
  // Maximum //
  /////////////

  auto max = BinarySearchTree.Maximum();
  std::cout << "Maximum()";
  std::cout << " = ";
  if (max) {
    std::cout << max->GetKey() << std::endl;
  }

  ////////////
  // Height //
  ////////////

  std::cout << "Height()";
  std::cout << " = ";
  std::cout << BinarySearchTree.Height() << std::endl;

  ////////////
  // Height //
  ////////////

  std::cout << "Size()";
  std::cout << " = ";
  std::cout << BinarySearchTree.Size() << std::endl;

  ///////////
  // Clear //
  ///////////

  BinarySearchTree.Clear();
  std::cout << "Clear()" << std::endl;

  return 0;
}
