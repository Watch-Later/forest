#pragma once

#include <memory>
#include <string>
#include <unordered_map>

template <typename T> class trie {
private:
  struct Node {
    std::unordered_map<T, std::shared_ptr<Node>> children;
    bool end = false;
  };
  std::shared_ptr<Node> root = std::make_shared<Node>();

public:
  void insert(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current = root;
    for (const T &c : key) {
      if (current->children.find(c) == current->children.end())
        current->children[c] = std::make_shared<Node>();
      current = current->children[c];
    }
    current->end = true;
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
};