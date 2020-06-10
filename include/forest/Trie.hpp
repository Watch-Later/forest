#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

namespace forest {
template <typename T> class Trie {
private:
  struct TrieNode {
    std::unordered_map<T, std::shared_ptr<TrieNode>> children;
    bool end = false;
  };
  std::shared_ptr<TrieNode> root = std::make_shared<TrieNode>();
  size_t numWords = 0;

public:
  Trie() = default;

  auto size() { return this->numWords; }

  void insert(const std::basic_string<T> &key) {
    std::shared_ptr<TrieNode> current = root;
    for (const T &c : key) {
      if (current->children.find(c) == current->children.end())
        current->children[c] = std::make_shared<TrieNode>();
      current = current->children[c];
    }
    if (!current->end && current != root) {
      current->end = true;
      ++this->numWords;
    }
  }

  bool search(const std::basic_string<T> &key) {
    std::shared_ptr<TrieNode> current = root;
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

    std::shared_ptr<TrieNode> current = root;
    std::stack<std::shared_ptr<TrieNode>> stk;

    stk.push(current);

    for (const T &c : key) {
      if (current->children.empty())
        return false;
      current = current->children[c];
      if (!current)
        return false;
      stk.push(current);
    }

    // If No Prefix is matched or The prefix is not a Legit word.
    if (stk.size() <= 1 || !stk.top()->end)
      return false;

    stk.top()->end = false;
    auto r_itr = key.rbegin();

    // Remove a Node Iteratively when it is not a word and it has no children.
    while (!stk.top()->end && stk.top()->children.empty() &&
           r_itr != key.rend()) {
      stk.pop();
      stk.top()->children.erase(*r_itr);
      ++r_itr;
    }

    --this->numWords;
    return true;
  }
};

} // namespace forest
