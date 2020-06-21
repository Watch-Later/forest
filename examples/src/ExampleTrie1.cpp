#include <forest/Trie.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

int main() {
  forest::Trie<char> Trie;

  Trie.insert("కంప్యూటర్");
  Trie.insert("கணக்கிடும் பொறி");
  Trie.insert("संगणक");
  Trie.insert("Computer");
  Trie.insert("υπολογιστή");
  Trie.insert("компьютер");

  cout << Trie.size() << endl;
  cout << Trie.search("கணக்கிடும் பொற") << endl;
  cout << Trie.search("కంప్యూటర్") << endl;
  cout << Trie.remove("комп") << endl;

  cout << Trie.remove("υπολογιστή") << endl;

  Trie.insert("Computer Science");
  cout << Trie.size() << endl;
  cout << Trie.search("संगणक") << endl;

  // Example for using predict in trie
  Trie.insert("Chemical");
  Trie.insert("Computer");
  Trie.insert("computer modelling");
  Trie.insert("Computer Science");
  Trie.insert("Computer Engineering");
  Trie.insert("Computer Networking");
  Trie.insert("Computer Architecture");

  auto vec = Trie.predict("Computer");

  // Print Contents of a Vector to Console
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::basic_string<char>>(std::cout, "\n"));

  // Erase the contents of the Trie using clear() method
  Trie.clear();

  // Check for Size
  cout << Trie.size() << endl;
  cout << Trie.search("కంప్యూటర్") << endl;
}