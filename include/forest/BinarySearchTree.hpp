#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <queue>
#include <utility>

namespace forest {
template <typename T> class BinarySearchTree;

template <typename T> class BinarySearchTreeNodeBase {
  template <typename U> friend class BinarySearchTree;

private:
  T *mLeft{nullptr};
  T *mRight{nullptr};

private:
  std::size_t mHeight{1};

public:
  BinarySearchTreeNodeBase() = default;
  ~BinarySearchTreeNodeBase() = default;
  BinarySearchTreeNodeBase(const BinarySearchTreeNodeBase &other) {
    mHeight = other.mHeight;
  }
  BinarySearchTreeNodeBase(BinarySearchTreeNodeBase &&other) {
    mHeight = other.mHeight;
    other.mHeight = 1;
  }

public:
  BinarySearchTreeNodeBase &operator=(const BinarySearchTreeNodeBase &other) {
    if (&other == this)
      return *this;
    mHeight = other.mHeight;
    return *this;
  }
  BinarySearchTreeNodeBase &operator=(BinarySearchTreeNodeBase &&other) {
    if (&other == this)
      return *this;
    mHeight = other.mHeight;
    other.mHeight = 1;
    return *this;
  }
};

template <typename T> class BinarySearchTree {
public:
  using Callback = std::function<void(T &)>;

private:
  T *mRoot{nullptr};

private:
  void PreOrderTraversal(T *root, const Callback &callback) {
    if (!root)
      return;
    callback(*root);
    PreOrderTraversal(root->mLeft, callback);
    PreOrderTraversal(root->mRight, callback);
  }
  void InOrderTraversal(T *root, const Callback &callback) {
    if (!root)
      return;
    InOrderTraversal(root->mLeft, callback);
    callback(*root);
    InOrderTraversal(root->mRight, callback);
  }
  void PostOrderTraversal(T *root, const Callback &callback) {
    if (!root)
      return;
    PostOrderTraversal(root->mLeft, callback);
    PostOrderTraversal(root->mRight, callback);
    callback(*root);
  }
  void BreadthFirstTraversal(T *root, const Callback &callback) {
    if (!root)
      return;
    std::queue<T *> queue;
    queue.push(root);
    while (!queue.empty()) {
      T *current{queue.front()};
      callback(*current);
      queue.pop();
      if (current->mLeft)
        queue.push(current->mLeft);
      if (current->mRight)
        queue.push(current->mRight);
    }
  }

private:
  T *Minimum(T *root) {
    if (!root)
      return nullptr;
    while (root->mLeft)
      root = root->mLeft;
    return root;
  }
  T *Maximum(T *root) {
    if (!root)
      return nullptr;
    while (root->mRight)
      root = root->mRight;
    return root;
  }

private:
  std::size_t Height(const T *root) {
    if (!root)
      return 0;
    return root->mHeight;
  }
  std::size_t Size(const T *root) {
    if (!root)
      return 0;
    return Size(root->mLeft) + Size(root->mRight) + 1;
  }

private:
  T *Insert(T *root, const T &node) {
    if (!root)
      return new T(node);
    if (node < *root)
      root->mLeft = Insert(root->mLeft, node);
    else if (*root < node)
      root->mRight = Insert(root->mRight, node);
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable> T *Remove(T *root, const Comparable &key) {
    if (!root)
      return nullptr;
    if (key < *root)
      root->mLeft = Remove(root->mLeft, key);
    else if (*root < key)
      root->mRight = Remove(root->mRight, key);
    else {
      if (!root->mLeft && !root->mRight) {
        delete root;
        root = nullptr;
      } else if (!root->mLeft) {
        T *tmp{root};
        root = root->mRight;
        delete tmp;
        tmp = nullptr;
      } else if (!root->mRight) {
        T *tmp{root};
        root = root->mLeft;
        delete tmp;
        tmp = nullptr;
      } else {
        T *min{Minimum(root->mRight)};
        *root = *min;
        root->mRight = Remove(root->mRight, *min);
      }
    }
    if (!root)
      return nullptr;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable> T *Search(T *root, const Comparable &key) {
    while (root) {
      if (key < *root)
        root = root->mLeft;
      else if (*root < key)
        root = root->mRight;
      else
        return root;
    }
    return nullptr;
  }

private:
  void Clear(T *root) {
    if (!root)
      return;
    if (root->mLeft)
      Clear(root->mLeft);
    if (root->mRight)
      Clear(root->mRight);
    delete root;
    root = nullptr;
  }

public:
  BinarySearchTree() = default;
  ~BinarySearchTree() { Clear(); }
  BinarySearchTree(const BinarySearchTree &) = delete;
  BinarySearchTree(BinarySearchTree &&other) {
    mRoot = other.mRoot;
    other.mRoot = nullptr;
  }

public:
  BinarySearchTree &operator=(const BinarySearchTree &) = delete;
  BinarySearchTree &operator=(BinarySearchTree &&other) {
    if (&other == this)
      return *this;
    mRoot = other.mRoot;
    other.mRoot = nullptr;
    return *this;
  }

public:
  void PreOrderTraversal(const Callback &callback) {
    PreOrderTraversal(mRoot, callback);
  }
  void InOrderTraversal(const Callback &callback) {
    InOrderTraversal(mRoot, callback);
  }
  void PostOrderTraversal(const Callback &callback) {
    PostOrderTraversal(mRoot, callback);
  }
  void BreadthFirstTraversal(const Callback &callback) {
    BreadthFirstTraversal(mRoot, callback);
  }

public:
  T *Minimum() { return Minimum(mRoot); }
  T *Maximum() { return Maximum(mRoot); }

public:
  std::size_t Height() { return Height(mRoot); }
  std::size_t Size() { return Size(mRoot); }

public:
  void Insert(const T &node) { mRoot = Insert(mRoot, node); }
  template <typename Key> void Remove(const Key &key) {
    mRoot = Remove(mRoot, key);
  }
  template <typename Key> T *Search(const Key &key) {
    return Search(mRoot, key);
  }

public:
  void Clear() {
    Clear(mRoot);
    mRoot = nullptr;
  }
};
} // namespace forest