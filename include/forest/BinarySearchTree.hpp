#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <queue>
#include <utility>

namespace forest {
template <typename Node>
class BinarySearchTree;

template <typename Node>
class BinarySearchTreeNodeBase {
  template <typename T>
  friend class BinarySearchTree;

 private:
  Node *mLeft{nullptr};
  Node *mRight{nullptr};

 private:
  unsigned mHeight{1};

 public:
  BinarySearchTreeNodeBase() = default;
  ~BinarySearchTreeNodeBase() = default;
};

template <typename Node>
class BinarySearchTree {
 public:
  using Callback = std::function<void(Node &)>;

 private:
  Node *mRoot{nullptr};

 private:
  void PreOrderTraversal(Node *root, Callback callback) {
    if (!root) return;
    callback(*root);
    PreOrderTraversal(root->mLeft, callback);
    PreOrderTraversal(root->mRight, callback);
  }
  void InOrderTraversal(Node *root, Callback callback) {
    if (!root) return;
    InOrderTraversal(root->mLeft, callback);
    callback(*root);
    InOrderTraversal(root->mRight, callback);
  }
  void PostOrderTraversal(Node *root, Callback callback) {
    if (!root) return;
    PostOrderTraversal(root->mLeft, callback);
    PostOrderTraversal(root->mRight, callback);
    callback(*root);
  }
  void BreadthFirstTraversal(Node *root, Callback callback) {
    if (!root) return;
    std::queue<Node *> queue;
    queue.push(root);
    while (!queue.empty()) {
      Node *current{queue.front()};
      callback(*current);
      queue.pop();
      if (current->mLeft) queue.push(current->mLeft);
      if (current->mRight) queue.push(current->mRight);
    }
  }

 private:
  Node *Minimum(Node *root) {
    if (!root) return nullptr;
    while (root->mLeft) root = root->mLeft;
    return root;
  }
  Node *Maximum(Node *root) {
    if (!root) return nullptr;
    while (root->mRight) root = root->mRight;
    return root;
  }

 private:
  unsigned Height(const Node *root) {
    if (!root) return 0;
    return root->mHeight;
  }
  unsigned Size(const Node *root) {
    if (!root) return 0;
    return Size(root->mLeft) + Size(root->mRight) + 1;
  }

 private:
  Node *Insert(Node *root, const Node &node) {
    if (!root) return new Node(node);
    if (node < *root)
      root->mLeft = Insert(root->mLeft, node);
    else if (*root < node)
      root->mRight = Insert(root->mRight, node);
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable>
  Node *Remove(Node *root, const Comparable &query) {
    if (!root) return nullptr;
    if (query < *root)
      root->mLeft = Remove(root->mLeft, query);
    else if (*root < query)
      root->mRight = Remove(root->mRight, query);
    else {
      if (!root->mLeft && !root->mRight) {
        delete root;
        root = nullptr;
      } else if (!root->mLeft) {
        Node *tmp{root};
        root = root->mRight;
        delete tmp;
        tmp = nullptr;
      } else if (!root->mRight) {
        Node *tmp{root};
        root = root->mLeft;
        delete tmp;
        tmp = nullptr;
      } else {
        Node *min{Minimum(root->mRight)};
        *root = *min;
        root->mRight = Remove(root->mRight, *min);
      }
    }
    if (!root) return nullptr;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable>
  Node *Search(Node *root, const Comparable &query) {
    while (root) {
      if (query < *root)
        root = root->mLeft;
      else if (*root < query)
        root = root->mRight;
      else
        return root;
    }
    return nullptr;
  }

 private:
  void Clear(Node *root) {
    if (!root) return;
    if (root->mLeft) Clear(root->mLeft);
    if (root->mRight) Clear(root->mRight);
    delete root;
    root = nullptr;
  }

 public:
  BinarySearchTree() = default;
  BinarySearchTree(const BinarySearchTree &) = delete;
  BinarySearchTree(BinarySearchTree &&) = delete;
  ~BinarySearchTree() { Clear(); }

 public:
  BinarySearchTree &operator=(const BinarySearchTree &) = delete;
  BinarySearchTree &operator=(BinarySearchTree &&) = delete;

 public:
  void PreOrderTraversal(Callback callback) { PreOrderTraversal(mRoot, callback); }
  void InOrderTraversal(Callback callback) { InOrderTraversal(mRoot, callback); }
  void PostOrderTraversal(Callback callback) {
    PostOrderTraversal(mRoot, callback);
  }
  void BreadthFirstTraversal(Callback callback) {
    BreadthFirstTraversal(mRoot, callback);
  }

 public:
  Node *Minimum() { return Minimum(mRoot); }
  Node *Maximum() { return Maximum(mRoot); }

 public:
  unsigned Height() { return Height(mRoot); }
  unsigned Size() { return Size(mRoot); }

 public:
  void Insert(const Node &node) { mRoot = Insert(mRoot, node); }
  template <typename Comparable>
  void Remove(const Comparable &query) {
    mRoot = Remove(mRoot, query);
  }
  template <typename Comparable>
  Node *Search(const Comparable &query) {
    return Search(mRoot, query);
  }

 public:
  void Clear() {
    Clear(mRoot);
    mRoot = nullptr;
  }
};
}  // namespace forest
