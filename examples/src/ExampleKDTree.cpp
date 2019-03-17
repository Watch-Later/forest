#include <forest/KDTree.hpp>
#include <iostream>

int main() {
  forest::KDTree<float, 4> KDTree;

  forest::KDTree<float, 4>::Points points{
      {0, 6, 0, 6}, {1, 5, 1, 5}, {2, 4, 2, 4}, {3, 3, 3, 3},
      {4, 2, 4, 2}, {5, 1, 5, 1}, {6, 0, 6, 0},
  };

  KDTree.fill(points.begin(), points.end());

  std::cout << "search({ 6, 0, 6, 0 })";
  std::cout << " = ";
  if (KDTree.search({6, 0, 6, 0})) {
    std::cout << "Found" << std::endl;
  } else {
    std::cout << "Not Found" << std::endl;
  }

  std::cout << "size()";
  std::cout << " = ";
  std::cout << KDTree.size() << std::endl;

  std::cout << "remove({ 3, 3, 3, 3 })" << std::endl;
  KDTree.remove({3, 3, 3, 3});

  std::cout << "size()";
  std::cout << " = ";
  std::cout << KDTree.size() << std::endl;

  std::cout << "search({ 3, 3, 3, 3 })";
  std::cout << " = ";
  if (KDTree.search({3, 3, 3, 3})) {
    std::cout << "Found" << std::endl;
  } else {
    std::cout << "Not Found" << std::endl;
  }

  std::cout << "query({ { 3, 3, 3, 3 }, { 2, 2, 2, 2 } })";
  std::cout << " = {" << std::endl;
  KDTree.query({{3, 3, 3, 3}, {2, 2, 2, 2}}, [](auto point) {
    std::cout << "(" << point[0] << ", " << point[1] << ", " << point[2] << ", "
              << point[3] << ")" << std::endl;
  });
  std::cout << "}" << std::endl;

  std::cout << "clear()" << std::endl;
  KDTree.clear();

  std::cout << "size()";
  std::cout << " = ";
  std::cout << KDTree.size() << std::endl;

  return 0;
}
