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
template <typename T> forest::AVLTree
template <typename T> forest::BinarySearchTree
```

## Node Base Classes

```cpp
template <typename T> forest::AVLTreeNodeBase
template <typename T> forest::BinarySearchTreeNodeBase
```

### Node Class Example #1

```cpp
#include <forest/AVLTree.hpp>
#include <string>

class Node : public forest::AVLTreeNodeBase<Node> { // Inherit from Node Base
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

### Node Class Example #2

```cpp
#include <forest/BinarySearchTree.hpp>
#include <string>

class Node : public forest::BinarySearchTreeNodeBase<Node> { // Inherit from Node Base
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

## Tree Functions

### Tree Traversals

```cpp
void PreOrderTraversal(const Callback &callback)
void InOrderTraversal(const Callback &callback)
void PostOrderTraversal(const Callback &callback)
void BreadthFirstTraversal(const Callback &callback)
```

#### Example

```cpp
Tree.PreOrderTraversal([](auto &node) {
  // TODO
});
Tree.InOrderTraversal([](auto &node) {
  // TODO
});
Tree.PostOrderTraversal([](auto &node) {
  // TODO
});
Tree.BreadthFirstTraversal([](auto &node) {
  // TODO
});
```

### Tree Minimum / Maximum

```cpp
T *Minimum()
T *Maximum()
```

#### Example

```cpp
auto min = Tree.Minimum();
auto max = Tree.Maximum();
```

### Tree Height / Size

```cpp
std::size_t Height()
std::size_t Size()
```

#### Example

```cpp
auto height = Tree.Height();
auto size = Tree.Size();
```

### Tree Insert / Remove / Search
```cpp
void Insert(const T &node)
template <typename Key> void Remove(const Key &key)
template <typename Key> T *Search(const Key &key)
```

#### Example

```cpp
Tree.Insert(Node(key, value));
Tree.Remove(key);
auto result = Tree.Search(key);
if (result) {
  std::cout << "Found" << std::endl;
} else {
  std::cout << "Not Found" << std::endl;
}
```

### Tree Clear
```cpp
void Clear()
```

#### Example

```cpp
Tree.Clear();
```

# Credits

- Icon made by Freepik from www.flaticon.com
