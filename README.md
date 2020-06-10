# Template Library of Tree Data Structures in C++17
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-3-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->
![C/C++ CI](https://github.com/xorz57/forest/workflows/C/C++%20CI/badge.svg)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![CodeFactor](https://www.codefactor.io/repository/github/xorz57/forest/badge/master)](https://www.codefactor.io/repository/github/xorz57/forest/overview/master)

# Example 1
```cpp
#include <forest/AVLTree.hpp>
// #include <forest/BinarySearchTree.hpp>
#include <iostream>

int main() {
  forest::AVLTree<int> Tree;
  // forest::BinarySearchTree<int> Tree;

  Tree.insert(2);
  Tree.insert(4);
  Tree.insert(90);
  Tree.insert(3);
  Tree.insert(0);
  Tree.insert(14);
  Tree.insert(45);

  Tree.pre_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.in_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.post_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.breadth_first_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  if (auto min = Tree.minimum()) {
    std::cout << "min: " << min->get() << std::endl;
  }

  if (auto max = Tree.maximum()) {
    std::cout << "max: " << max->get() << std::endl;
  }

  Tree.remove(2);

  if (auto res = Tree.search(2)) {
    std::cout << "res: " << res->get() << std::endl;
  }

  Tree.clear();

  return 0;
}
```

# Example 2
```cpp
#include <forest/AVLTree.hpp>
// #include <forest/BinarySearchTree.hpp>
#include <iostream>
#include <string>

class Node {
public:
  Node() = default;
  Node(int key, const std::string &value) : mKey(key), mValue(value){};
  ~Node() = default;

public:
  bool operator<(const Node &other) const { return mKey < other.mKey; }
  friend bool operator<(const Node &, const int);
  friend bool operator<(const int, const Node &);
  friend std::ostream &operator<<(std::ostream &, const Node &);

public:
  void setKey(int key) { mKey = key; }
  void setValue(const std::string &value) { mValue = value; }

public:
  int getKey() { return mKey; }
  std::string getValue() { return mValue; }

private:
  int mKey = 0;
  std::string mValue;
};

bool operator<(const Node &lhs, const int rhs) { return lhs.mKey < rhs; }
bool operator<(const int lhs, const Node &rhs) { return lhs < rhs.mKey; }
std::ostream &operator<<(std::ostream &os, const Node &node) {
  os << "(" << node.mKey << ", " << node.mValue << ")" << std::endl;
  return os;
}

int main() {
  forest::AVLTree<Node> Tree;
  // forest::BinarySearchTree<Node> Tree;

  Tree.insert(Node(2 , "Thor"));
  Tree.insert(Node(4 , "Odin"));
  Tree.insert(Node(90, "Loki"));
  Tree.insert(Node(3 , "Baldr"));
  Tree.insert(Node(0 , "Frigg"));
  Tree.insert(Node(14, "Eir"));
  Tree.insert(Node(45, "Heimdall"));

  Tree.pre_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.in_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.post_order_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  Tree.breadth_first_traversal([](auto node) {
    std::cout << node << std::endl;
  });

  if (auto min = Tree.minimum()) {
    std::cout << "min: " << min->get() << std::endl;
  }

  if (auto max = Tree.maximum()) {
    std::cout << "max: " << max->get() << std::endl;
  }

  Tree.remove(2);

  if (auto res = Tree.search(2)) {
    std::cout << "res: " << res->get() << std::endl;
  }

  Tree.clear();

  return 0;
}
```

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):
<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://linkedin.com/in/vivek-reddy-karri/"><img src="https://avatars1.githubusercontent.com/u/25481823?v=4" width="100px;" alt=""/><br /><sub><b>Vivek Reddy</b></sub></a><br /><a href="https://github.com/xorz57/forest/commits?author=VivekReddy98" title="Code">💻</a> <a href="https://github.com/xorz57/forest/commits?author=VivekReddy98" title="Tests">⚠️</a></td>
    <td align="center"><a href="https://github.com/MatusKysel"><img src="https://avatars3.githubusercontent.com/u/6115866?v=4" width="100px;" alt=""/><br /><sub><b>Matus Kysel</b></sub></a><br /><a href="https://github.com/xorz57/forest/commits?author=MatusKysel" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/xorz57"><img src="https://avatars0.githubusercontent.com/u/1548352?v=4" width="100px;" alt=""/><br /><sub><b>George Fotopoulos</b></sub></a><br /><a href="https://github.com/xorz57/forest/commits?author=xorz57" title="Code">💻</a> <a href="#infra-xorz57" title="Infrastructure (Hosting, Build-Tools, etc)">🚇</a> <a href="https://github.com/xorz57/forest/commits?author=xorz57" title="Tests">⚠️</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!
