cmake_minimum_required(VERSION 3.10)

project("Forest Examples" LANGUAGES CXX)

###############################################################################
# Add Examples
###############################################################################

forest_add_example(ExampleAVLTree "src/ExampleAVLTree.cpp")
forest_add_example(ExampleBinarySearchTree "src/ExampleBinarySearchTree.cpp")
