#pragma once

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>

namespace forest {
template <typename BinarySearchTreeNode>
class BinarySearchTree;

template <typename BinarySearchTreeNode>
class BinarySearchTreeNodeBase {
  template <typename T>
  friend class BinarySearchTree;

 private:
  BinarySearchTreeNode *mLeft{nullptr};
  BinarySearchTreeNode *mRight{nullptr};

 private:
  unsigned mHeight{1};

 public:
  BinarySearchTreeNodeBase() = default;
  BinarySearchTreeNodeBase &operator=(const BinarySearchTreeNodeBase &other) {
    mHeight = other.mHeight;
    return *this;
  }
  ~BinarySearchTreeNodeBase() = default;
};

template <typename BinarySearchTreeNode>
class BinarySearchTree {
 public:
  using Callback = std::function<void(BinarySearchTreeNode &)>;

 private:
  BinarySearchTreeNode *mRoot{nullptr};

 private:
  void PreOrderTraversal(BinarySearchTreeNode *root, const Callback callback) {
    if (!root) return;
    callback(*root);
    PreOrderTraversal(root->mLeft, callback);
    PreOrderTraversal(root->mRight, callback);
  }
  void InOrderTraversal(BinarySearchTreeNode *root, const Callback callback) {
    if (!root) return;
    InOrderTraversal(root->mLeft, callback);
    callback(*root);
    InOrderTraversal(root->mRight, callback);
  }
  void PostOrderTraversal(BinarySearchTreeNode *root, const Callback callback) {
    if (!root) return;
    PostOrderTraversal(root->mLeft, callback);
    PostOrderTraversal(root->mRight, callback);
    callback(*root);
  }
  void BreadthFirstTraversal(BinarySearchTreeNode *root,
                             const Callback callback) {
    if (!root) return;
    std::queue<BinarySearchTreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      BinarySearchTreeNode *current{queue.front()};
      callback(*current);
      queue.pop();
      if (current->mLeft) queue.push(current->mLeft);
      if (current->mRight) queue.push(current->mRight);
    }
  }

 private:
  BinarySearchTreeNode *Minimum(BinarySearchTreeNode *root) {
    if (!root) return nullptr;
    while (root->mLeft) root = root->mLeft;
    return root;
  }
  BinarySearchTreeNode *Maximum(BinarySearchTreeNode *root) {
    if (!root) return nullptr;
    while (root->mRight) root = root->mRight;
    return root;
  }

 private:
  unsigned Height(const BinarySearchTreeNode *root) {
    if (!root) return 0;
    return root->mHeight;
  }
  unsigned Size(const BinarySearchTreeNode *root) {
    if (!root) return 0;
    return Size(root->mLeft) + Size(root->mRight) + 1;
  }

 private:
  BinarySearchTreeNode *Insert(BinarySearchTreeNode *root,
                               const BinarySearchTreeNode &node) {
    if (!root) return new BinarySearchTreeNode(node);
    if (node < *root)
      root->mLeft = Insert(root->mLeft, node);
    else if (*root < node)
      root->mRight = Insert(root->mRight, node);
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable>
  BinarySearchTreeNode *Remove(BinarySearchTreeNode *root,
                               const Comparable &query) {
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
        BinarySearchTreeNode *tmp{root};
        root = root->mRight;
        delete tmp;
        tmp = nullptr;
      } else if (!root->mRight) {
        BinarySearchTreeNode *tmp{root};
        root = root->mLeft;
        delete tmp;
        tmp = nullptr;
      } else {
        BinarySearchTreeNode *min{Minimum(root->mRight)};
        *root = *min;
        root->mRight = Remove(root->mRight, *min);
      }
    }
    if (!root) return nullptr;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    return root;
  }
  template <typename Comparable>
  BinarySearchTreeNode *Search(BinarySearchTreeNode *root,
                               const Comparable &query) {
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
  void Clear(BinarySearchTreeNode *root) {
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
  void PreOrderTraversal(const Callback callback) {
    PreOrderTraversal(mRoot, callback);
  }
  void InOrderTraversal(const Callback callback) {
    InOrderTraversal(mRoot, callback);
  }
  void PostOrderTraversal(const Callback callback) {
    PostOrderTraversal(mRoot, callback);
  }
  void BreadthFirstTraversal(const Callback callback) {
    BreadthFirstTraversal(mRoot, callback);
  }

 public:
  BinarySearchTreeNode *Minimum() { return Minimum(mRoot); }
  BinarySearchTreeNode *Maximum() { return Maximum(mRoot); }

 public:
  unsigned Height() { return Height(mRoot); }
  unsigned Size() { return Size(mRoot); }

 public:
  void Insert(const BinarySearchTreeNode &node) { mRoot = Insert(mRoot, node); }
  template <typename Comparable>
  void Remove(const Comparable &query) {
    mRoot = Remove(mRoot, query);
  }
  template <typename Comparable>
  BinarySearchTreeNode *Search(const Comparable &query) {
    return Search(mRoot, query);
  }

 public:
  void Clear() {
    Clear(mRoot);
    mRoot = nullptr;
  }
};
}  // namespace forest