#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/BinarySearchTree.hpp>

SCENARIO("Test Binary Search Tree") {
  GIVEN("An empty Binary Search Tree") {
    forest::BinarySearchTree<int> BinarySearchTree;
    REQUIRE(BinarySearchTree.height() == 0);
    REQUIRE(BinarySearchTree.size() == 0);
    REQUIRE(BinarySearchTree.minimum() == std::nullopt);
    REQUIRE(BinarySearchTree.maximum() == std::nullopt);
    REQUIRE(BinarySearchTree.search(GENERATE(-1, 0, 1)) == std::nullopt);
    WHEN("I insert nodes with keys from 0 up to 9 inclusive") {
      for (int key = 0; key < 10; ++key) {
        BinarySearchTree.insert(key);
      }
      REQUIRE(BinarySearchTree.height() == 10);
      REQUIRE(BinarySearchTree.size() == 10);
      AND_WHEN("I want the node with the minimum key") {
        auto min = BinarySearchTree.minimum();
        THEN("This node exists") {
          REQUIRE(min != std::nullopt);
          CHECK(min->get() == 0);
        }
      }
      AND_WHEN("I want the node with the maximum key") {
        auto max = BinarySearchTree.maximum();
        THEN("This node exists") {
          REQUIRE(max != std::nullopt);
          CHECK(max->get() == 9);
        }
      }
      AND_WHEN("I search for a node with a key that doesn't exist") {
        int key = GENERATE(-1, 10);
        auto result = BinarySearchTree.search(key);
        THEN("This node dosn't exist") { REQUIRE(result == std::nullopt); }
      }
      AND_WHEN("I search for a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        auto result = BinarySearchTree.search(key);
        THEN("This node exists") {
          REQUIRE(result != std::nullopt);
          CHECK(result->get() == key);
        }
      }
      AND_WHEN("I remove a node with a key that exists") {
        int key = GENERATE(range(0, 9));
        BinarySearchTree.remove(key);
        THEN("This node exists") {
          REQUIRE(BinarySearchTree.search(key) == std::nullopt);
          CHECK(BinarySearchTree.height() == 9);
          CHECK(BinarySearchTree.size() == 9);
        }
      }
      AND_WHEN("I clear the Binary Search Tree") {
        BinarySearchTree.clear();
        THEN("The height and the size of the Binary Search Tree change") {
          REQUIRE(BinarySearchTree.height() == 0);
          REQUIRE(BinarySearchTree.size() == 0);
        }
      }
    }
  }
}