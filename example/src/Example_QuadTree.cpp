#include <forest/QuadTree.hpp>
#include <iostream>

int main() {
  forest::QuadTree<float, 2> QuadTree({{0, 0}, {10, 10}});

  for (float i = -5; i < 5; ++i) {
    std::cout << "insert({ " << i << ", " << i << " })" << std::endl;
    QuadTree.insert({i, i});
  }

  std::cout << std::endl;

  for (float i = 0; i < 15; ++i) {
    std::cout << "search({ " << i << ", " << i << " })"
              << " = ";
    if (QuadTree.search({i, i})) {
      std::cout << "Found" << std::endl;
    } else {
      std::cout << "Not Found" << std::endl;
    }
  }

  std::cout << std::endl;

  for (float i = 0; i < 5; ++i) {
    std::cout << "remove({ " << i << ", " << i << " })" << std::endl;
    QuadTree.remove({i, i});
  }

  std::cout << std::endl;

  std::cout << "query({ 0, 0, 10, 10 })"
            << " = {" << std::endl;
  QuadTree.query({{0, 0}, {10, 10}}, [](auto point) {
    std::cout << "(" << point[0] << ", " << point[1] << ")" << std::endl;
  });
  std::cout << "}" << std::endl;

  std::cout << std::endl;

  std::cout << "clear()" << std::endl;
  QuadTree.clear();

  return 0;
}
