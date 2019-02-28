cmake_minimum_required(VERSION 3.1...3.13)

project(forest_test LANGUAGES CXX)

###############################################################################
# Add Tests
###############################################################################

forest_add_test(Test_AVLTree src/Test_AVLTree.cpp)
forest_add_test(Test_BinarySearchTree src/Test_BinarySearchTree.cpp)
forest_add_test(Test_KDTree src/Test_KDTree.cpp)
forest_add_test(Test_QuadTree src/Test_QuadTree.cpp)