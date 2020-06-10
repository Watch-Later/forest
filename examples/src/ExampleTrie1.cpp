#include <forest/Trie.hpp>
#include <iostream>

using namespace std;

int main(){
    forest::Trie<char> Trie; 

    Trie.insert("కంప్యూటర్");
    Trie.insert("கணக்கிடும் பொறி");
    Trie.insert("संगणक");
    Trie.insert("Computer");
    Trie.insert("υπολογιστή");
    Trie.insert("компьютер");

    cout << Trie.size() << endl;
    cout << Trie.search("கணக்கிடும் பொற")  << endl;
    cout << Trie.search("కంప్యూటర్")  << endl;
    cout << Trie.remove("комп")  << endl;

    cout << Trie.remove("υπολογιστή")  << endl;

    Trie.insert("Computer Science");
    cout << Trie.size() << endl;
    cout << Trie.search("संगणक")  << endl;
}