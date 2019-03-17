#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

//////////
// Node //
//////////

class Node : public forest::BinarySearchTreeNodeBase<Node> {
 public:
  Node() = default;
  Node(const int& KEY, const std::string& VALUE) : key(KEY), value(VALUE){};
  ~Node() = default;

 public:
  bool operator<(const Node& other) const { return key < other.key; }
  friend bool operator<(const Node& lhs, int rhs);
  friend bool operator<(int lhs, const Node& rhs);

 public:
  void SetKey(int KEY) { key = KEY; }
  void SetValue(std::string VALUE) { value = VALUE; }

 public:
  int GetKey() { return key; }
  std::string GetValue() { return value; }

 private:
  int key;
  std::string value;
};

bool operator<(const Node& lhs, int rhs) { return lhs.key < rhs; }
bool operator<(int lhs, const Node& rhs) { return lhs < rhs.key; }

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
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  ////////////////////////
  // In Order Traversal //
  ////////////////////////

  std::cout << "InOrderTraversal()";
  std::cout << " = ";
  BinarySearchTree.InOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  //////////////////////////
  // Post Order Traversal //
  //////////////////////////

  std::cout << "PostOrderTraversal()";
  std::cout << " = ";
  BinarySearchTree.PostOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  /////////////////////////////
  // Breadth First Traversal //
  /////////////////////////////

  std::cout << "BreadthFirstTraversal()";
  std::cout << " = ";
  BinarySearchTree.BreadthFirstTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
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
