#include <forest/AVLTree.hpp>
#include <iostream>
#include <string>

//////////
// Node //
//////////

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

int main() {
  forest::AVLTree<Node> AVLTree;

  ////////////
  // Insert //
  ////////////

  AVLTree.Insert(Node(2, "Thor"));
  AVLTree.Insert(Node(4, "Odin"));
  AVLTree.Insert(Node(90, "Loki"));
  AVLTree.Insert(Node(3, "Baldr"));
  AVLTree.Insert(Node(0, "Frigg"));
  AVLTree.Insert(Node(14, "Eir"));
  AVLTree.Insert(Node(45, "Heimdall"));

  /////////////////////////
  // Pre Order Traversal //
  /////////////////////////

  std::cout << "PreOrderTraversal()";
  std::cout << " = ";
  AVLTree.PreOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  ////////////////////////
  // In Order Traversal //
  ////////////////////////

  std::cout << "InOrderTraversal()";
  std::cout << " = ";
  AVLTree.InOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  //////////////////////////
  // Post Order Traversal //
  //////////////////////////

  std::cout << "PostOrderTraversal()";
  std::cout << " = ";
  AVLTree.PostOrderTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  /////////////////////////////
  // Breadth First Traversal //
  /////////////////////////////

  std::cout << "BreadthFirstTraversal()";
  std::cout << " = ";
  AVLTree.BreadthFirstTraversal(
      [](auto &node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  ////////////
  // Remove //
  ////////////

  AVLTree.Remove(3);
  std::cout << "Remove(3)" << std::endl;

  ////////////
  // Search //
  ////////////

  auto result = AVLTree.Search(3);
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

  auto min = AVLTree.Minimum();
  std::cout << "Minimum()";
  std::cout << " = ";
  if (min) {
    std::cout << min->GetKey() << std::endl;
  }

  /////////////
  // Maximum //
  /////////////

  auto max = AVLTree.Maximum();
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
  std::cout << AVLTree.Height() << std::endl;

  ////////////
  // Height //
  ////////////

  std::cout << "Size()";
  std::cout << " = ";
  std::cout << AVLTree.Size() << std::endl;

  ///////////
  // Clear //
  ///////////

  AVLTree.Clear();
  std::cout << "Clear()" << std::endl;

  return 0;
}
