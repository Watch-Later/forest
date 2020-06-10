#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

namespace forest {
template <typename T> class Trie {
private:
  struct Node {
    std::unordered_map<T, std::shared_ptr<Node>> children;
    bool end = false;
  };
  std::shared_ptr<Node> root = std::make_shared<Node>();
  std::size_t mSize = 0;

public:
  Trie() = default;

  auto size() { return this->mSize; }

  void insert(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current = root;
    for (const T &c : key) {
      if (current->children.find(c) == current->children.end())
        current->children[c] = std::make_shared<Node>();
      current = current->children[c];
    }
    if (!current->end && current != root) {
      current->end = true;
      ++this->mSize;
    }
  }

  bool search(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current = root;
    for (const T &c : key) {
      if (current->children.empty())
        return false;
      current = current->children[c];
      if (!current)
        return false;
    }
    return current->end;
  }

  bool remove(const std::basic_string<T> &key) {
    if (root->children.empty())
      return false;
    std::shared_ptr<Node> current = root;
    std::stack<std::shared_ptr<Node>> stack;
    stack.push(current);
    for (const T &c : key) {
      if (current->children.empty())
        return false;
      current = current->children[c];
      if (!current)
        return false;
      stack.push(current);
    }
    // If No Prefix is matched or The prefix is not a Legit word.
    if (stack.size() <= 1 || !stack.top()->end)
      return false;
    stack.top()->end = false;
    auto r_it = key.rbegin();
    // Remove a Node Iteratively when it is not a word and it has no children.
    while (!stack.top()->end && stack.top()->children.empty() &&
           r_it != key.rend()) {
      stack.pop();
      stack.top()->children.erase(*r_it);
      ++r_it;
    }
    --this->mSize;
    return true;
  }
};

} // namespace forest
