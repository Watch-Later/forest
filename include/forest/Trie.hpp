#pragma once

#include <cstdint>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace forest {
template <typename T> class Trie {
private:
  struct Node {
    std::unordered_map<T, std::shared_ptr<Node>> children;
    bool end = false;
  };

private:
  std::shared_ptr<Node> mRoot{std::make_shared<Node>()};
  std::uintmax_t mSize{0};

public:
  Trie() = default;

public:
  void insert(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current{mRoot};
    for (const T &c : key) {
      if (current->children.find(c) == current->children.end())
        current->children[c] = std::make_shared<Node>();
      current = current->children[c];
    }
    if (!current->end && current != mRoot) {
      current->end = true;
      ++this->mSize;
    }
  }

  bool search(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current{mRoot};
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
    std::shared_ptr<Node> current{mRoot};
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

  void clear(){
     this->mRoot->children.clear();
     this->mSize = 0;
  }

public:
  auto size() { return this->mSize; }

private:
  static std::vector<std::basic_string<T>> recursive_predict(const std::pair<const T, std::shared_ptr<Node>>& map_entry) {   
    std::vector<std::basic_string<T>> result;
    if (!map_entry.second->children.empty()) {
        std::vector<std::vector<std::basic_string<T>>> result2d;
        std::transform(map_entry.second->children.begin(), map_entry.second->children.end(),  
                                                std::back_inserter(result2d), forest::Trie<T>::recursive_predict);
        std::for_each(result2d.begin(), result2d.end(), [&result](std::vector<std::basic_string<T>>& d) 
                                                {std::move(d.begin(), d.end(), std::back_inserter(result));});
        std::for_each(result.begin(), result.end(), [&map_entry](std::basic_string<T>& d) {d.insert(0, &(map_entry.first), 1);});
    }

    // If the suffix ending at this node is a legit word by itself and also has other children. 
    // Eg (cat, cattle) If Prefix = ca, Output should also include cat & cattle.
    if (map_entry.second->end) { 
        std::basic_string<T> str(1, map_entry.first);
        result.push_back(str);
    }
    return result; 
  }  

public:
  std::vector<std::basic_string<T>> predict(const std::basic_string<T> &key) {
    std::shared_ptr<Node> current{mRoot};
    for (const T &c : key) {
      if (current->children.empty())
        return {};
      current = current->children[c];
      if (!current)
        return {};
    }
    if (current->children.empty()) return {}; 
    std::vector<std::basic_string<T>> result;
    std::vector<std::vector<std::basic_string<T>>> result2d;

    // Recursively return all the Legit Words of every direct child in this node (i.e. a vector for every node & 
    // thus a 2D vector to collect all the Predicted Suffixes.
    std::transform(current->children.begin(), current->children.end(),  
                                    std::back_inserter(result2d), forest::Trie<T>::recursive_predict);
    
    // Flatten out the 2D-Array.
    std::for_each(result2d.begin(), result2d.end(), [&result](std::vector<std::basic_string<T>>& d) 
                                    {std::move(d.begin(), d.end(), std::back_inserter(result));});
    
    // Append the input prefix to the found suffixes.
    std::for_each(result.begin(), result.end(), [&key](std::basic_string<T>& d) { d.insert(0, key);});

    return result;
  }
};

} // namespace forest
