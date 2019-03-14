#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <queue>
#include <utility>

namespace forest {
template <typename Key, typename Value>
class AVLTree {
 public:
  using Callback = std::function<void(const Key &, Value &)>;

 private:
  class AVLTreeNode {
    friend class AVLTree;

   private:
    AVLTreeNode *mLeft{nullptr};
    AVLTreeNode *mRight{nullptr};

   private:
    unsigned mHeight{1};

   public:
    Key key;
    Value value;

   public:
    AVLTreeNode() = default;
    AVLTreeNode(const Key &KEY, const Value &VALUE) : key(KEY), value(VALUE) {}
    AVLTreeNode(const AVLTreeNode &) = delete;
    AVLTreeNode(AVLTreeNode &&) = delete;
    AVLTreeNode &operator=(const AVLTreeNode &) = delete;
    AVLTreeNode &operator=(AVLTreeNode &&) = delete;
    ~AVLTreeNode() = default;
  };

 private:
  AVLTreeNode *mRoot{nullptr};

 private:
  void PreOrderTraversal(AVLTreeNode *root, const Callback callback) {
    if (!root) return;
    callback(root->key, root->value);
    PreOrderTraversal(root->mLeft, callback);
    PreOrderTraversal(root->mRight, callback);
  }
  void InOrderTraversal(AVLTreeNode *root, const Callback callback) {
    if (!root) return;
    InOrderTraversal(root->mLeft, callback);
    callback(root->key, root->value);
    InOrderTraversal(root->mRight, callback);
  }
  void PostOrderTraversal(AVLTreeNode *root, const Callback callback) {
    if (!root) return;
    PostOrderTraversal(root->mLeft, callback);
    PostOrderTraversal(root->mRight, callback);
    callback(root->key, root->value);
  }
  void BreadthFirstTraversal(AVLTreeNode *root, const Callback callback) {
    if (!root) return;
    std::queue<AVLTreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      AVLTreeNode *current{queue.front()};
      callback(current->key, current->value);
      queue.pop();
      if (current->mLeft) queue.push(current->mLeft);
      if (current->mRight) queue.push(current->mRight);
    }
  }

 private:
  AVLTreeNode *Minimum(AVLTreeNode *root) {
    if (!root) return nullptr;
    while (root->mLeft) root = root->mLeft;
    return root;
  }
  AVLTreeNode *Maximum(AVLTreeNode *root) {
    if (!root) return nullptr;
    while (root->mRight) root = root->mRight;
    return root;
  }

 private:
  int Balance(const AVLTreeNode *root) {
    if (!root) return 0;
    return Height(root->mLeft) - Height(root->mRight);
  }

 private:
  unsigned Height(const AVLTreeNode *root) {
    if (!root) return 0;
    return root->mHeight;
  }
  unsigned Size(const AVLTreeNode *root) {
    if (!root) return 0;
    return Size(root->mLeft) + Size(root->mRight) + 1;
  }

 private:
  AVLTreeNode *RotateRight(AVLTreeNode *root) {
    AVLTreeNode *pivot{root->mLeft};
    AVLTreeNode *orphan{pivot->mRight};
    pivot->mRight = root;
    root->mLeft = orphan;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    pivot->mHeight = std::max(Height(pivot->mLeft), Height(pivot->mRight)) + 1;
    return pivot;
  }
  AVLTreeNode *RotateLeft(AVLTreeNode *root) {
    AVLTreeNode *pivot{root->mRight};
    AVLTreeNode *orphan{pivot->mLeft};
    pivot->mLeft = root;
    root->mRight = orphan;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    pivot->mHeight = std::max(Height(pivot->mLeft), Height(pivot->mRight)) + 1;
    return pivot;
  }

 private:
  AVLTreeNode *Insert(AVLTreeNode *root, const Key &key, const Value &value) {
    if (!root) return new AVLTreeNode(key, value);
    if (key < root->key)
      root->mLeft = Insert(root->mLeft, key, value);
    else if (key > root->key)
      root->mRight = Insert(root->mRight, key, value);
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    if (Balance(root) > 1) {
      if (key < root->mLeft->key) {
        return RotateRight(root);
      }
      if (key > root->mLeft->key) {
        root->mLeft = RotateLeft(root->mLeft);
        return RotateRight(root);
      }
    } else if (Balance(root) < -1) {
      if (key > root->mRight->key) {
        return RotateLeft(root);
      }
      if (key < root->mRight->key) {
        root->mRight = RotateRight(root->mRight);
        return RotateLeft(root);
      }
    }
    return root;
  }

  AVLTreeNode *Remove(AVLTreeNode *root, const Key &key) {
    if (!root) return nullptr;
    if (key < root->key)
      root->mLeft = Remove(root->mLeft, key);
    else if (key > root->key)
      root->mRight = Remove(root->mRight, key);
    else {
      if (!root->mLeft && !root->mRight) {
        delete root;
        root = nullptr;
      } else if (!root->mLeft) {
        AVLTreeNode *tmp{root};
        root = root->mRight;
        delete tmp;
        tmp = nullptr;
      } else if (!root->mRight) {
        AVLTreeNode *tmp{root};
        root = root->mLeft;
        delete tmp;
        tmp = nullptr;
      } else {
        AVLTreeNode *min{Minimum(root->mRight)};
        root->key = min->key;
        root->value = min->value;
        root->mRight = Remove(root->mRight, min->key);
      }
    }
    if (!root) return nullptr;
    root->mHeight = std::max(Height(root->mLeft), Height(root->mRight)) + 1;
    if (Balance(root) > 1) {
      if (Balance(root->mLeft) >= 0) {
        return RotateRight(root);
      }
      root->mLeft = RotateLeft(root->mLeft);
      return RotateRight(root);
    }
    if (Balance(root) < -1) {
      if (Balance(root->mRight) <= 0) {
        return RotateLeft(root);
      }
      root->mRight = RotateRight(root->mRight);
      return RotateLeft(root);
    }
    return root;
  }

  AVLTreeNode *Search(AVLTreeNode *root, const Key &key) {
    while (root) {
      if (key > root->key) {
        root = root->mRight;
      } else if (key < root->key) {
        root = root->mLeft;
      } else {
        return root;
      }
    }
    return nullptr;
  }

 private:
  void Clear(AVLTreeNode *root) {
    if (!root) return;
    if (root->mLeft) Clear(root->mLeft);
    if (root->mRight) Clear(root->mRight);
    delete root;
    root = nullptr;
  }

 public:
  AVLTree() = default;
  AVLTree(const AVLTree &) = delete;
  AVLTree(AVLTree &&) = delete;
  AVLTree &operator=(const AVLTree &) = delete;
  AVLTree &operator=(AVLTree &&) = delete;
  ~AVLTree() { Clear(); }

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
  AVLTreeNode *Minimum() { return Minimum(mRoot); }
  AVLTreeNode *Maximum() { return Maximum(mRoot); }

 public:
  unsigned Height() { return Height(mRoot); }
  unsigned Size() { return Size(mRoot); }

 public:
  void Insert(const Key &key, const Value &value) {
    mRoot = Insert(mRoot, key, value);
  }
  void Remove(const Key &key) { mRoot = Remove(mRoot, key); }
  AVLTreeNode *Search(const Key &key) { return Search(mRoot, key); }

 public:
  void Clear() {
    Clear(mRoot);
    mRoot = nullptr;
  }
};
}  // namespace forest
