#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>

SCENARIO("Test AVL Tree") {
  GIVEN("An empty AVL Tree") {
    forest::AVLTree<int> tree;
    REQUIRE(tree.height() == 0);
    REQUIRE(tree.size() == 0);
    REQUIRE(tree.minimum() == std::nullopt);
    REQUIRE(tree.maximum() == std::nullopt);
    REQUIRE(tree.search(GENERATE(-1, 0, 1)) == std::nullopt);
    WHEN("I insert nodes with keys from 0 up to 9 inclusive") {
      for (int key = 0; key < 10; ++key) {
        tree.insert(key);
      }
      REQUIRE(tree.height() == 4);
      REQUIRE(tree.size() == 10);
      AND_WHEN("I want the node with the minimum key") {
        auto min = tree.minimum();
        REQUIRE(min != std::nullopt);
        CHECK(min->get() == 0);
      }
      AND_WHEN("I want the node with the maximum key") {
        auto max = tree.maximum();
        REQUIRE(max != std::nullopt);
        CHECK(max->get() == 9);
      }
      AND_WHEN("I search for a node with a key that doesn't exist") {
        int key = GENERATE(-1, 10);
        auto result = tree.search(key);
        THEN("This node doesn't exist") { REQUIRE(result == std::nullopt); }
      }
      AND_WHEN("I search for a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        auto result = tree.search(key);
        REQUIRE(result != std::nullopt);
        CHECK(result->get() == key);
      }
      AND_WHEN("I remove a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        tree.remove(key);
        REQUIRE(tree.search(key) == std::nullopt);
        CHECK(tree.height() == 4);
        CHECK(tree.size() == 9);
      }
      AND_WHEN("I clear the AVL Tree") {
        tree.clear();
        REQUIRE(tree.height() == 0);
        REQUIRE(tree.size() == 0);
      }
    }
  }
}
