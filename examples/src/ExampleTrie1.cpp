#include <forest/Trie.hpp>
#include <iostream>

using namespace std;

int main(){

    forest::Trie<char> Trie; 

    Trie.insert("కంప్యూటర్");
    Trie.insert("संगणक");
    Trie.insert("Computer");
    Trie.insert("υπολογιστή");
    Trie.insert("компьютер");

    cout << Trie.size() << endl;
    cout << Trie.search("కంప్యూటర్")  << endl;
    cout << Trie.remove("комп")  << endl;

    Trie.insert("Computer Science");
    cout << Trie.size() << endl;
    cout << Trie.search("संगणक")  << endl;

    /*-------------------------------------------------*/

    forest::Trie<char16_t> trie;

    trie.insert(u"υπολογιστής");
    trie.insert(u"computer");
    trie.insert(u"కంప్యూటర్");

    cout << trie.search(u"కంప్యూటర్") << endl;
    cout << trie.remove(u"संगणक") << endl;
}