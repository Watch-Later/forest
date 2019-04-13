![Logo](logo.png)

[![Build Status](https://ci.appveyor.com/api/projects/status/8e5jutnq0a8b458f/branch/master?svg=true)](https://ci.appveyor.com/project/xorz57/forest/branch/master)
[![Build Status](https://travis-ci.org/xorz57/forest.svg?branch=master)](https://travis-ci.org/xorz57/forest)
[![CodeFactor](https://www.codefactor.io/repository/github/xorz57/forest/badge/master)](https://www.codefactor.io/repository/github/xorz57/forest/overview/master)

# API

## Headers

```cpp
#include <forest/AVLTree.hpp>
#include <forest/BinarySearchTree.hpp>
```

## Tree Classes

```cpp
template <typename T> forest::AVLTree;
template <typename T> forest::BinarySearchTree;
```

## Node Base Classes

```cpp
template <typename T> forest::AVLTreeNodeBase;
template <typename T> forest::BinarySearchTreeNodeBase;
```

# Examples

## AVL Tree Example

```cpp
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

int main() {
  forest::AVLTree<Node> AVLTree;

  // TODO

  return 0;
}
```

## Binary Search Tree Example

```cpp
#include <forest/BinarySearchTree.hpp>
#include <string>

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

  // TODO

  return 0;
}
```

# Credits

- Icon made by Freepik from www.flaticon.com
