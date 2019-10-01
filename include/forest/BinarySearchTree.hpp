#pragma once

#include <algorithm>
#include <functional>
#include <optional>
#include <queue>

namespace forest {
template <typename T> class BinarySearchTree {
public:
  using Callback = std::function<void(const T &)>;

private:
  class BinarySearchTreeNode {
    friend class BinarySearchTree;

  private:
    BinarySearchTreeNode *mLeft{nullptr};
    BinarySearchTreeNode *mRight{nullptr};

  private:
    int mHeight{1};

  public:
    T mKey;

  public:
    BinarySearchTreeNode() = default;

    BinarySearchTreeNode(const T &key) : mKey(key) {}

    BinarySearchTreeNode(const BinarySearchTreeNode &) = delete;
    BinarySearchTreeNode(BinarySearchTreeNode &&) = delete;
    ~BinarySearchTreeNode() = default;

  public:
    BinarySearchTreeNode &operator=(const BinarySearchTreeNode &) = delete;
    BinarySearchTreeNode &operator=(BinarySearchTreeNode &&) = delete;
  };

private:
  BinarySearchTreeNode *mRoot{nullptr};

private:
  void pre_order_traversal(BinarySearchTreeNode *root, Callback callback) {
    if (!root)
      return;
    callback(root->mKey);
    pre_order_traversal(root->mLeft, callback);
    pre_order_traversal(root->mRight, callback);
  }

  void in_order_traversal(BinarySearchTreeNode *root, Callback callback) {
    if (!root)
      return;
    in_order_traversal(root->mLeft, callback);
    callback(root->mKey);
    in_order_traversal(root->mRight, callback);
  }

  void post_order_traversal(BinarySearchTreeNode *root, Callback callback) {
    if (!root)
      return;
    post_order_traversal(root->mLeft, callback);
    post_order_traversal(root->mRight, callback);
    callback(root->mKey);
  }

  void breadth_first_traversal(BinarySearchTreeNode *root, Callback callback) {
    if (!root)
      return;
    std::queue<BinarySearchTreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      BinarySearchTreeNode *current{queue.front()};
      callback(current->mKey);
      queue.pop();
      if (current->mLeft)
        queue.push(current->mLeft);
      if (current->mRight)
        queue.push(current->mRight);
    }
  }

private:
  BinarySearchTreeNode *minimum(BinarySearchTreeNode *root) {
    if (!root)
      return nullptr;
    while (root->mLeft)
      root = root->mLeft;
    return root;
  }

  BinarySearchTreeNode *maximum(BinarySearchTreeNode *root) {
    if (!root)
      return nullptr;
    while (root->mRight)
      root = root->mRight;
    return root;
  }

private:
  auto height(const BinarySearchTreeNode *root) {
    if (!root)
      return 0;
    return root->mHeight;
  }

  auto size(const BinarySearchTreeNode *root) {
    if (!root)
      return 0;
    return size(root->mLeft) + size(root->mRight) + 1;
  }

private:
  BinarySearchTreeNode *insert(BinarySearchTreeNode *root, const T &key) {
    if (!root)
      return new BinarySearchTreeNode(key);
    if (key < root->mKey)
      root->mLeft = insert(root->mLeft, key);
    else if (root->mKey < key)
      root->mRight = insert(root->mRight, key);
    root->mHeight = std::max(height(root->mLeft), height(root->mRight)) + 1;
    return root;
  }

  template <typename U>
  BinarySearchTreeNode *remove(BinarySearchTreeNode *root, const U &key) {
    if (!root)
      return nullptr;
    if (key < root->mKey)
      root->mLeft = remove(root->mLeft, key);
    else if (root->mKey < key)
      root->mRight = remove(root->mRight, key);
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
        BinarySearchTreeNode *min{minimum(root->mRight)};
        root->mKey = min->mKey;
        root->mRight = remove(root->mRight, min->mKey);
        // BinarySearchTreeNode * max{ maximum(root->mLeft) };
        // root->mKey = max->mKey;
        // root->mLeft = remove(root->mLeft, max->mKey);
      }
    }

    if (!root)
      return nullptr;

    root->mHeight = std::max(height(root->mLeft), height(root->mRight)) + 1;

    return root;
  }

  template <typename U>
  BinarySearchTreeNode *search(BinarySearchTreeNode *root, const U &key) {
    while (root) {
      if (root->mKey < key)
        root = root->mRight;
      else if (key < root->mKey)
        root = root->mLeft;
      else
        return root;
    }
    return nullptr;
  }

private:
  void clear(BinarySearchTreeNode *root) {
    if (!root)
      return;
    if (root->mLeft)
      clear(root->mLeft);
    if (root->mRight)
      clear(root->mRight);
    delete root;
    root = nullptr;
  }

public:
  BinarySearchTree() = default;

  BinarySearchTree(const BinarySearchTree &) = delete;
  BinarySearchTree(BinarySearchTree &&) = delete;

  ~BinarySearchTree() { clear(); }

public:
  BinarySearchTree &operator=(const BinarySearchTree &) = delete;
  BinarySearchTree &operator=(BinarySearchTree &&) = delete;

public:
  void pre_order_traversal(Callback callback) {
    pre_order_traversal(mRoot, callback);
  }

  void in_order_traversal(Callback callback) {
    in_order_traversal(mRoot, callback);
  }

  void post_order_traversal(Callback callback) {
    post_order_traversal(mRoot, callback);
  }

  void breadth_first_traversal(Callback callback) {
    breadth_first_traversal(mRoot, callback);
  }

public:
  auto minimum() {
    auto min = minimum(mRoot);
    return min ? std::optional<std::reference_wrapper<T>>{min->mKey}
               : std::nullopt;
  }

  auto maximum() {
    auto max = maximum(mRoot);
    return max ? std::optional<std::reference_wrapper<T>>{max->mKey}
               : std::nullopt;
  }

public:
  auto height() { return height(mRoot); }

  auto size() { return size(mRoot); }

public:
  void insert(const T &key) { mRoot = insert(mRoot, key); }

  template <typename U> void remove(const U &key) {
    mRoot = remove(mRoot, key);
  }

  template <typename U> auto search(const U &key) {
    auto res = search(mRoot, key);
    return res ? std::optional<std::reference_wrapper<T>>{res->mKey}
               : std::nullopt;
  }

public:
  void clear() {
    clear(mRoot);
    mRoot = nullptr;
  }
};
} // namespace forest
