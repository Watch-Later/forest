cmake_minimum_required(VERSION 3.1...3.13)

project("forest_benchmarks" LANGUAGES CXX)

###############################################################################
# Add Benchmarks
###############################################################################

forest_add_benchmark(BenchmarkAVLTree "src/BenchmarkAVLTree.cpp")
forest_add_benchmark(BenchmarkBinarySearchTree "src/BenchmarkBinarySearchTree.cpp")
