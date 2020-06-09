#include <forest/Trie.hpp>
#include <iostream>

using namespace std;

int main(){

    forest::Trie<char16_t> Trie;

    Trie.insert(u"కంప్యూటర్");
    Trie.insert(u"கணக்கிடும் பொறி");
    Trie.insert(u"संगणक");
    Trie.insert(u"Computer");
    Trie.insert(u"υπολογιστή");
    Trie.insert(u"компьютер");

    cout << Trie.size() << endl;
    cout << Trie.search(u"கணக்கிடும் பொற")  << endl;
    cout << Trie.search(u"కంప్యూటర్")  << endl;
    cout << Trie.remove(u"комп")  << endl;

    cout << Trie.remove(u"υπολογιστή")  << endl;
    
    Trie.insert(u"Computer Science");
    cout << Trie.size() << endl;
    cout << Trie.search(u"संगणक")  << endl;
}