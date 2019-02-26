cmake_minimum_required(VERSION 3.1...3.13)

project(forest_benchmark LANGUAGES CXX)

add_executable(Benchmark_AVLTree "src/Benchmark_AVLTree.cpp")
add_executable(Benchmark_BinarySearchTree "src/Benchmark_BinarySearchTree.cpp")
add_executable(Benchmark_KDTree "src/Benchmark_KDTree.cpp")
add_executable(Benchmark_QuadTree "src/Benchmark_QuadTree.cpp")

target_link_libraries(Benchmark_AVLTree benchmark forest)
target_link_libraries(Benchmark_BinarySearchTree benchmark forest)
target_link_libraries(Benchmark_KDTree benchmark forest)
target_link_libraries(Benchmark_QuadTree benchmark forest)
