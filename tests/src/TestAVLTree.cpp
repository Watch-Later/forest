#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>

SCENARIO("Test AVL Tree") {
  GIVEN("An empty AVL Tree") {
    forest::AVLTree<int> AVLTree;
    REQUIRE(AVLTree.height() == 0);
    REQUIRE(AVLTree.size() == 0);
    REQUIRE(AVLTree.minimum() == std::nullopt);
    REQUIRE(AVLTree.maximum() == std::nullopt);
    REQUIRE(AVLTree.search(GENERATE(-1, 0, 1)) == std::nullopt);
    WHEN("I insert nodes with keys from 0 up to 9 inclusive") {
      for (int key = 0; key < 10; ++key) {
        AVLTree.insert(key);
      }
      REQUIRE(AVLTree.height() == 4);
      REQUIRE(AVLTree.size() == 10);
      AND_WHEN("I want the node with the minimum key") {
        auto min = AVLTree.minimum();
        REQUIRE(min != std::nullopt);
        CHECK(min->get() == 0);
      }
      AND_WHEN("I want the node with the maximum key") {
        auto max = AVLTree.maximum();
        REQUIRE(max != std::nullopt);
        CHECK(max->get() == 9);
      }
      AND_WHEN("I search for a node with a key that doesn't exist") {
        int key = GENERATE(-1, 10);
        auto result = AVLTree.search(key);
        THEN("This node doesn't exist") { REQUIRE(result == std::nullopt); }
      }
      AND_WHEN("I search for a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        auto result = AVLTree.search(key);
        REQUIRE(result != std::nullopt);
        CHECK(result->get() == key);
      }
      AND_WHEN("I remove a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        AVLTree.remove(key);
        REQUIRE(AVLTree.search(key) == std::nullopt);
        CHECK(AVLTree.height() == 4);
        CHECK(AVLTree.size() == 9);
      }
      AND_WHEN("I clear the AVL Tree") {
        AVLTree.clear();
        REQUIRE(AVLTree.height() == 0);
        REQUIRE(AVLTree.size() == 0);
      }
    }
  }
}
