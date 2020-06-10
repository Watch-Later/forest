#include <forest/Trie.hpp>
#include <iostream>

using namespace std;

int main(){
    forest::Trie<wchar_t> Trie;

    Trie.insert(L"కంప్యూటర్");
    Trie.insert(L"கணக்கிடும் பொறி");
    Trie.insert(L"संगणक");
    Trie.insert(L"Computer");
    Trie.insert(L"υπολογιστή");
    Trie.insert(L"компьютер");

    cout << Trie.size() << endl;
    cout << Trie.search(L"கணக்கிடும் பொற")  << endl;
    cout << Trie.search(L"కంప్యూటర్")  << endl;
    cout << Trie.remove(L"комп")  << endl;

    cout << Trie.remove(L"υπολογιστή")  << endl;
    
    Trie.insert(L"Computer Science");
    cout << Trie.size() << endl;
    cout << Trie.search(L"संगणक")  << endl;
}
