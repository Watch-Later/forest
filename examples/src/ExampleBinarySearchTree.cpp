#include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

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

  BinarySearchTree.Insert(Node(2, "Thor"));
  BinarySearchTree.Insert(Node(4, "Odin"));
  BinarySearchTree.Insert(Node(90, "Loki"));
  BinarySearchTree.Insert(Node(3, "Baldr"));
  BinarySearchTree.Insert(Node(0, "Frigg"));
  BinarySearchTree.Insert(Node(14, "Eir"));
  BinarySearchTree.Insert(Node(45, "Heimdall"));

  std::cout << "PreOrderTraversal() = ";
  BinarySearchTree.PreOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "InOrderTraversal() = ";
  BinarySearchTree.InOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "PostOrderTraversal() = ";
  BinarySearchTree.PostOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "Remove(3)" << std::endl;
  BinarySearchTree.Remove(3);

  std::cout << "Search(3) = ";
  auto result = BinarySearchTree.Search(3);
  if (result) {
    std::cout << "Found" << std::endl;
  } else {
    std::cout << "Not Found" << std::endl;
  }

  std::cout << "Minimum() = ";
  auto min = BinarySearchTree.Minimum();
  if (min) {
    std::cout << min->GetKey() << std::endl;
  }

  std::cout << "Maximum() = ";
  auto max = BinarySearchTree.Maximum();
  if (max) {
    std::cout << max->GetKey() << std::endl;
  }

  std::cout << "Height() = " << BinarySearchTree.Height() << std::endl;
  std::cout << "Size() = " << BinarySearchTree.Size() << std::endl;

  std::cout << "Clear()" << std::endl;
  BinarySearchTree.Clear();

  return 0;
}
