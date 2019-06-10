#pragma once

#include <algorithm>
#include <functional>
#include <optional>
#include <queue>

namespace forest {
template <typename T> class AVLTree {
public:
  using Callback = std::function<void(T &)>;

private:
  class AVLTreeNode {
    friend class AVLTree;

  private:
    AVLTreeNode *mLeft{nullptr};
    AVLTreeNode *mRight{nullptr};

  private:
    unsigned height{1};

  public:
    T mKey;

  public:
    AVLTreeNode() = default;

    AVLTreeNode(const T &key) : mKey(key) {}

    AVLTreeNode(const AVLTreeNode &) = delete;
    AVLTreeNode(AVLTreeNode &&) = delete;
    AVLTreeNode &operator=(const AVLTreeNode &) = delete;
    AVLTreeNode &operator=(AVLTreeNode &&) = delete;
    ~AVLTreeNode() = default;
  };

private:
  AVLTreeNode *mRoot{nullptr};

private:
  void pre_order_traversal(AVLTreeNode *root, Callback callback) {
    if (!root)
      return;
    callback(root->mKey);
    pre_order_traversal(root->mLeft, callback);
    pre_order_traversal(root->mRight, callback);
  }

  void in_order_traversal(AVLTreeNode *root, Callback callback) {
    if (!root)
      return;
    in_order_traversal(root->mLeft, callback);
    callback(root->mKey);
    in_order_traversal(root->mRight, callback);
  }

  void post_order_traversal(AVLTreeNode *root, Callback callback) {
    if (!root)
      return;
    post_order_traversal(root->mLeft, callback);
    post_order_traversal(root->mRight, callback);
    callback(root->mKey);
  }

  void breadth_first_traversal(AVLTreeNode *root, Callback callback) {
    if (!root)
      return;
    std::queue<AVLTreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      AVLTreeNode *current{queue.front()};
      callback(current->mKey);
      queue.pop();
      if (current->mLeft)
        queue.push(current->mLeft);
      if (current->mRight)
        queue.push(current->mRight);
    }
  }

private:
  AVLTreeNode *minimum(AVLTreeNode *root) {
    if (!root)
      return nullptr;
    while (root->mLeft)
      root = root->mLeft;
    return root;
  }

  AVLTreeNode *maximum(AVLTreeNode *root) {
    if (!root)
      return nullptr;
    while (root->mRight)
      root = root->mRight;
    return root;
  }

private:
  int balance(const AVLTreeNode *root) {
    if (!root)
      return 0;
    return height(root->mLeft) - height(root->mRight);
  }

private:
  unsigned height(const AVLTreeNode *root) {
    if (!root)
      return 0;
    return root->height;
  }

  unsigned size(const AVLTreeNode *root) {
    if (!root)
      return 0;
    return size(root->mLeft) + size(root->mRight) + 1;
  }

private:
  AVLTreeNode *rotate_mRight(AVLTreeNode *root) {
    AVLTreeNode *pivot{root->mLeft};
    AVLTreeNode *orphan{pivot->mRight};

    pivot->mRight = root;
    root->mLeft = orphan;

    root->height = std::max(height(root->mLeft), height(root->mRight)) + 1;
    pivot->height = std::max(height(pivot->mLeft), height(pivot->mRight)) + 1;

    return pivot;
  }

  AVLTreeNode *rotate_mLeft(AVLTreeNode *root) {
    AVLTreeNode *pivot{root->mRight};
    AVLTreeNode *orphan{pivot->mLeft};

    pivot->mLeft = root;
    root->mRight = orphan;

    root->height = std::max(height(root->mLeft), height(root->mRight)) + 1;
    pivot->height = std::max(height(pivot->mLeft), height(pivot->mRight)) + 1;

    return pivot;
  }

private:
  AVLTreeNode *insert(AVLTreeNode *root, const T &key) {
    if (!root)
      return new AVLTreeNode(key);
    if (key < root->mKey)
      root->mLeft = insert(root->mLeft, key);
    else if (root->mKey < key)
      root->mRight = insert(root->mRight, key);

    root->height = std::max(height(root->mLeft), height(root->mRight)) + 1;

    if (balance(root) > 1) {
      if (key < root->mLeft->mKey) {
        return rotate_mRight(root);
      }
      if (root->mLeft->mKey < key) {
        root->mLeft = rotate_mLeft(root->mLeft);
        return rotate_mRight(root);
      }
    } else if (balance(root) < -1) {
      if (root->mRight->mKey < key) {
        return rotate_mLeft(root);
      }
      if (key < root->mRight->mKey) {
        root->mRight = rotate_mRight(root->mRight);
        return rotate_mLeft(root);
      }
    }

    return root;
  }

  template <typename U> AVLTreeNode *remove(AVLTreeNode *root, const U &key) {
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
        AVLTreeNode *min{minimum(root->mRight)};
        root->mKey = min->mKey;
        root->mRight = remove(root->mRight, min->mKey);
        // AVLTreeNode * max{ maximum(root->mLeft) };
        // root->mKey = max->mKey;
        // root->mLeft = remove(root->mLeft, max->mKey);
      }
    }

    if (!root)
      return nullptr;

    root->height = std::max(height(root->mLeft), height(root->mRight)) + 1;

    if (balance(root) > 1) {
      if (balance(root->mLeft) >= 0) {
        return rotate_mRight(root);
      }
      root->mLeft = rotate_mLeft(root->mLeft);
      return rotate_mRight(root);
    }
    if (balance(root) < -1) {
      if (balance(root->mRight) <= 0) {
        return rotate_mLeft(root);
      }
      root->mRight = rotate_mRight(root->mRight);
      return rotate_mLeft(root);
    }

    return root;
  }

  template <typename U> AVLTreeNode *search(AVLTreeNode *root, const U &key) {
    while (root) {
      if (root->mKey < key) {
        root = root->mRight;
      } else if (key < root->mKey) {
        root = root->mLeft;
      } else {
        return root;
      }
    }
    return nullptr;
  }

private:
  void clear(AVLTreeNode *root) {
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
  AVLTree() = default;

  AVLTree(const AVLTree &) = delete;
  AVLTree(AVLTree &&) = delete;
  AVLTree &operator=(const AVLTree &) = delete;
  AVLTree &operator=(AVLTree &&) = delete;

  ~AVLTree() { clear(); }

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
  unsigned height() { return height(mRoot); }

  unsigned size() { return size(mRoot); }

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
