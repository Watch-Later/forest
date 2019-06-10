cmake_minimum_required(VERSION 3.10)

project("Forest Benchmarks" LANGUAGES CXX)

###############################################################################
# Add Benchmarks
###############################################################################

forest_add_benchmark(BenchmarkAVLTree "src/BenchmarkAVLTree.cpp")
forest_add_benchmark(BenchmarkBinarySearchTree "src/BenchmarkBinarySearchTree.cpp")
