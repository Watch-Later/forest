/**
 * Trie Container
 * Methods Implemented: insert, search, remove, size
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <stack>

namespace forest{
template <typename T> class Trie {
private:

  struct TrieNode { // TrieNode  
    std::unordered_map<T, std::shared_ptr<TrieNode>> children;
    bool end = false; // If True, prefix ending with this Node is a word.
  };

  std::shared_ptr<TrieNode> root = std::make_shared<TrieNode>();

  long long numWords = 0;

public:

  Trie() = default; // Default Constructor;

  /**
   * Number of Legit Words in the Trie
   */ 
  auto size(){
    return this->numWords;
  }

  /**
   * Inserts an Element into the Trie
   */ 
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

  /**
   * Returns True if the String is Found
   *         False Otherwise
   */
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

  /**
   * Iterative Implementation of remove using a Stack.
   * Returns True if the String is Found & Deletes it.
   *         False Otherwise
   */
  bool remove(const std::basic_string<T> &key) {
    
    // If Trie is Empty, Immediately Return False
    if (root->children.empty())
        return false;

    std::shared_ptr<TrieNode> current = root;
    std::stack<std::shared_ptr<TrieNode>> stk;

    stk.push(current); // push the Root into the Stack.

    for(const T &c : key){
        if (current->children.empty())
            return false;
        current = current->children[c];
        if (!current)
          return false;
        stk.push(current); // Push all the Node Pointers if Present
    }

    // If No Prefix is matched or The prefix is not a Legit word. 
    if (stk.size() <= 1 || !stk.top()->end) return false;

    stk.top()->end = false;
    auto r_itr = key.rbegin();

    // Remove a Node Iteratively when it is not a word and it has no children.
    while (!stk.top()->end && stk.top()->children.empty() && r_itr != key.rend()){
        stk.pop();
        stk.top()->children.erase(*r_itr);
        ++r_itr;
    }

    --this->numWords;
    return true;
  }

};
  
}
