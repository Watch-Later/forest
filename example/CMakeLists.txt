cmake_minimum_required(VERSION 3.1...3.13)

project(forest_example LANGUAGES CXX)

add_executable(Example_AVLTree "src/Example_AVLTree.cpp")
add_executable(Example_BinarySearchTree "src/Example_BinarySearchTree.cpp")
add_executable(Example_KDTree "src/Example_KDTree.cpp")
add_executable(Example_QuadTree "src/Example_QuadTree.cpp")

target_link_libraries(Example_AVLTree forest)
target_link_libraries(Example_BinarySearchTree forest)
target_link_libraries(Example_KDTree forest)
target_link_libraries(Example_QuadTree forest)
