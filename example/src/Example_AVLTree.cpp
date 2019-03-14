#include <forest/AVLTree.hpp>
#include <iostream>
#include <string>

int main() {
    forest::AVLTree<int, std::string> AVLTree;

    AVLTree.Insert(2, "Thor");
    AVLTree.Insert(4, "Odin");
    AVLTree.Insert(90, "Loki");
    AVLTree.Insert(3, "Baldr");
    AVLTree.Insert(0, "Frigg");
    AVLTree.Insert(14, "Eir");
    AVLTree.Insert(45, "Einar");

    std::cout << "PreOrderTraversal()" << std::endl;
    AVLTree.PreOrderTraversal([](auto key, auto & value) {
        value += ".";
        std::cout << key << "->" << value << std::endl;
    });
    std::cout << std::endl;

    std::cout << "InOrderTraversal()" << std::endl;
    AVLTree.InOrderTraversal([](auto key, auto & value) {
        value += ".";
        std::cout << key << "->" << value << std::endl;
    });
    std::cout << std::endl;

    std::cout << "PostOrderTraversal()" << std::endl;
    AVLTree.PostOrderTraversal([](auto key, auto & value) {
        value += ".";
        std::cout << key << "->" << value << std::endl;
    });
    std::cout << std::endl;

    std::cout << "Remove(3)" << std::endl;
    AVLTree.Remove(3);

    std::cout << "search(3)" << " = ";
    auto result = AVLTree.Search(3);
    if (result) {
        std::cout << "Found" << std::endl;
    }
    else {
        std::cout << "Not Found" << std::endl;
    }

    std::cout << "minimum()" << " = ";
    auto min = AVLTree.Minimum();
    if (min) {
        std::cout << min->key << std::endl;
    }
    else {
        std::cout << "Not Found" << std::endl;
    }

    std::cout << "maximum()" << " = ";
    auto max = AVLTree.Maximum();
    if (max) {
        std::cout << max->key << std::endl;
    }
    else {
        std::cout << "Not Found" << std::endl;
    }

    std::cout << "height()" << " = " << AVLTree.Height() << std::endl;

    std::cout << "size()" << " = " << AVLTree.Size() << std::endl;

    AVLTree.Clear();

    return 0;
}
