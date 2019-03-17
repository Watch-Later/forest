#include <forest/AVLTree.hpp>
#include <iostream>
#include <string>

class Node : public forest::AVLTreeNodeBase<Node> {
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
  forest::AVLTree<Node> AVLTree;

  AVLTree.Insert(Node(2, "Thor"));
  AVLTree.Insert(Node(4, "Odin"));
  AVLTree.Insert(Node(90, "Loki"));
  AVLTree.Insert(Node(3, "Baldr"));
  AVLTree.Insert(Node(0, "Frigg"));
  AVLTree.Insert(Node(14, "Eir"));
  AVLTree.Insert(Node(45, "Heimdall"));

  std::cout << "PreOrderTraversal() = ";
  AVLTree.PreOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "InOrderTraversal() = ";
  AVLTree.InOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "PostOrderTraversal() = ";
  AVLTree.PostOrderTraversal(
      [](auto& node) { std::cout << node.GetKey() << " "; });
  std::cout << std::endl;

  std::cout << "Remove(3)" << std::endl;
  AVLTree.Remove(3);

  std::cout << "Search(3) = ";
  auto result = AVLTree.Search(3);
  if (result) {
    std::cout << "Found" << std::endl;
  } else {
    std::cout << "Not Found" << std::endl;
  }

  std::cout << "Minimum() = ";
  auto min = AVLTree.Minimum();
  if (min) {
    std::cout << min->GetKey() << std::endl;
  }

  std::cout << "Maximum() = ";
  auto max = AVLTree.Maximum();
  if (max) {
    std::cout << max->GetKey() << std::endl;
  }

  std::cout << "Height() = " << AVLTree.Height() << std::endl;
  std::cout << "Size() = " << AVLTree.Size() << std::endl;

  std::cout << "Clear()" << std::endl;
  AVLTree.Clear();

  return 0;
}
