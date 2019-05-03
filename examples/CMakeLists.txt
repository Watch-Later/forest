cmake_minimum_required(VERSION 3.1...3.13)

project("Forest Examples" LANGUAGES CXX)

###############################################################################
# Add Examples
###############################################################################

forest_add_example(ExampleAVLTree "src/ExampleAVLTree.cpp")
forest_add_example(ExampleBinarySearchTree "src/ExampleBinarySearchTree.cpp")
