#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/KDTree.hpp>

SCENARIO("Test KD Tree") {
  GIVEN("A KD Tree") {
    forest::KDTree<float, 2> KDTree;
    WHEN("The KD Tree is empty") {
      THEN("Test size()") { REQUIRE(KDTree.size() == 0); }
      THEN("Test maximum(0)") { REQUIRE(KDTree.maximum(0) == nullptr); }
      THEN("Test minimum(0)") { REQUIRE(KDTree.minimum(0) == nullptr); }
      THEN("Test search({ 0, 0 })") { REQUIRE(KDTree.search({0, 0}) == false); }
      THEN("Test remove({ 0 , 0 })") {
        KDTree.remove({0, 0});
        REQUIRE(KDTree.search({0, 0}) == false);
      }
      THEN("Test clear()") {
        KDTree.clear();
        REQUIRE(KDTree.size() == 0);
      }
      THEN("Test query({ { 0 , 0 }, { 1, 1 } })") {
        forest::KDTree<float, 2>::Points results;
        KDTree.query({{0, 0}, {1, 1}},
                     [&results](const forest::KDTree<float, 2>::Point& point) {
                       results.push_back(point);
                     });
        REQUIRE(results.empty() == true);
      }
    }
    WHEN("Nodes are inserted in random order") {
      forest::KDTree<float, 2>::Points points{{-3, 3}, {-2, 2}, {-1, 1}, {0, 0},
                                              {1, -1}, {2, -2}, {3, -3}};
      KDTree.fill(points.begin(), points.end());
      THEN("Test size()") { REQUIRE(KDTree.size() == 7); }
      THEN("Test maximum(0)") {
        auto max = KDTree.maximum(0);
        REQUIRE(max != nullptr);
        REQUIRE(max->point[0] == 3);
        REQUIRE(max->point[1] == -3);
      }
      THEN("Test minimum(0)") {
        auto min = KDTree.minimum(0);
        REQUIRE(min != nullptr);
        REQUIRE(min->point[0] == -3);
        REQUIRE(min->point[1] == 3);
      }
      THEN("Test maximum(1)") {
        auto max = KDTree.maximum(1);
        REQUIRE(max != nullptr);
        REQUIRE(max->point[0] == -3);
        REQUIRE(max->point[1] == 3);
      }
      THEN("Test minimum(1)") {
        auto min = KDTree.minimum(1);
        REQUIRE(min != nullptr);
        REQUIRE(min->point[0] == 3);
        REQUIRE(min->point[1] == -3);
      }
      THEN("Test search({ 0, 0 })") { REQUIRE(KDTree.search({0, 0}) == true); }
      THEN("Test search({ 2, -2 })") {
        REQUIRE(KDTree.search({2, -2}) != false);
      }
      THEN("Test remove({ 0 , 0 })") {
        KDTree.remove({0, 0});
        REQUIRE(KDTree.search({0, 0}) == false);
      }
      THEN("Test remove({ -3 , 3 })") {
        KDTree.remove({-3, 3});
        REQUIRE(KDTree.search({-3, 3}) == false);
      }
      THEN("Test remove({ 3 , -3 })") {
        KDTree.remove({3, -3});
        REQUIRE(KDTree.search({3, -3}) == false);
      }
      THEN("Test clear()") {
        KDTree.clear();
        REQUIRE(KDTree.size() == 0);
      }
      THEN("Test query({ { 0 , 0 }, { 5, 5 } })") {
        forest::KDTree<float, 2>::Points results;
        KDTree.query({{0, 0}, {5, 5}},
                     [&results](const forest::KDTree<float, 2>::Point& point) {
                       results.push_back(point);
                     });
        REQUIRE(results.size() == 7);
      }
    }
  }
}