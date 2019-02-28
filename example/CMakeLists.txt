cmake_minimum_required(VERSION 3.1...3.13)

project(forest_example LANGUAGES CXX)

###############################################################################
# Add Examples
###############################################################################

forest_add_example(Example_AVLTree src/Example_AVLTree.cpp)
forest_add_example(Example_BinarySearchTree src/Example_BinarySearchTree.cpp)
forest_add_example(Example_KDTree src/Example_KDTree.cpp)
forest_add_example(Example_QuadTree src/Example_QuadTree.cpp)
