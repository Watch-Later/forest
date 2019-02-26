cmake_minimum_required(VERSION 3.1...3.13)

project(forest_test LANGUAGES CXX)

add_executable(Test_AVLTree "src/Test_AVLTree.cpp")
add_executable(Test_BinarySearchTree "src/Test_BinarySearchTree.cpp")
add_executable(Test_KDTree "src/Test_KDTree.cpp")
add_executable(Test_QuadTree "src/Test_QuadTree.cpp")

target_link_libraries(Test_AVLTree Catch2 forest)
target_link_libraries(Test_BinarySearchTree Catch2 forest)
target_link_libraries(Test_KDTree Catch2 forest)
target_link_libraries(Test_QuadTree Catch2 forest)

add_test(AVLTree Test_AVLTree)
add_test(BinarySearchTree Test_BinarySearchTree)
add_test(KDTree Test_KDTree)
add_test(QuadTree Test_QuadTree)