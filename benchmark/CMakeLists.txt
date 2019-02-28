cmake_minimum_required(VERSION 3.1...3.13)

project(forest_benchmark LANGUAGES CXX)

###############################################################################
# Add Benchmarks
###############################################################################

forest_add_benchmark(Benchmark_AVLTree src/Benchmark_AVLTree.cpp)
forest_add_benchmark(Benchmark_BinarySearchTree src/Benchmark_BinarySearchTree.cpp)
forest_add_benchmark(Benchmark_KDTree src/Benchmark_KDTree.cpp)
forest_add_benchmark(Benchmark_QuadTree src/Benchmark_QuadTree.cpp)