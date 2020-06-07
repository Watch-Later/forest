/**
 * Trie Data Structure
 * Methods Implemented: insert, search, remove 
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <stack>

namespace forest{
template <typename T> class trie {
private:

  struct Node { // TrieNode  
    std::unordered_map<T, std::shared_ptr<Node>> children;
    bool end = false; // If True, prefix ending with this Node is a word.
    T val;
    Node() : val(0), end(false) {}
    Node(const T& val, const bool& end) : val(val), end(end) {}
  };

  std::shared_ptr<Node> root = std::make_shared<Node>();

public:

  void insert(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current = root;
    for (const T &c : key) {
      if (current->children.find(c) == current->children.end())
        current->children[c] = std::make_shared<Node>(new Node(c, false));
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

  bool remove(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current = root;
    char c;
    int i;

    std::stack<shared_ptr<TrieNode>> stk;

    stk.push(root);

    for(const T &c : key){
        if (current->children.empty())
            return false;
        current = current->children[c];
        if (!current)
          return false;
        stk.push(current);
    }

    stk.top()->end = false;

    std::basic_string<T>::r_itr = key.rbegin();

    while (!stk.top()->end && !stk.top()->children.empty() && r_itr != key.rend()){
        stk.pop();
        stk.top()->erase(*r_itr);
        ++r_itr;
    }

    return true;
  }

};
  
}