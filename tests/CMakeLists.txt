cmake_minimum_required(VERSION 3.1...3.13)

project("Forest Tests" LANGUAGES CXX)

###############################################################################
# Add Tests
###############################################################################

forest_add_test(TestAVLTree "src/TestAVLTree.cpp")
forest_add_test(TestBinarySearchTree "src/TestBinarySearchTree.cpp")
