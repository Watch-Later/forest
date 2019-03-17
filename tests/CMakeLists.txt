cmake_minimum_required(VERSION 3.1...3.13)

project("forest_tests" LANGUAGES CXX)

###############################################################################
# Add Tests
###############################################################################

forest_add_test(TestAVLTree "src/TestAVLTree.cpp")
forest_add_test(TestBinarySearchTree "src/TestBinarySearchTree.cpp")
forest_add_test(TestKDTree "src/TestKDTree.cpp")
forest_add_test(TestQuadTree "src/TestQuadTree.cpp")