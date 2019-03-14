#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>

SCENARIO("Test AVL Tree") {
  GIVEN("An AVL Tree") {
    forest::AVLTree<int, int> AVLTree;
    WHEN("The AVL Tree is empty") {
      THEN("Test size()") { REQUIRE(AVLTree.Size() == 0); }
      THEN("Test height()") { REQUIRE(AVLTree.Height() == 0); }
      THEN("Test maximum()") { REQUIRE(AVLTree.Maximum() == nullptr); }
      THEN("Test minimum()") { REQUIRE(AVLTree.Minimum() == nullptr); }
      THEN("Test search(555)") { REQUIRE(AVLTree.Search(555) == nullptr); }
      THEN("Test clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in random order") {
      AVLTree.Insert(4, 0);
      AVLTree.Insert(2, 0);
      AVLTree.Insert(90, 0);
      AVLTree.Insert(3, 0);
      AVLTree.Insert(0, 0);
      AVLTree.Insert(14, 0);
      AVLTree.Insert(45, 0);
      THEN("Test size()") { REQUIRE(AVLTree.Size() == 7); }
      THEN("Test height()") { REQUIRE(AVLTree.Height() == 3); }
      THEN("Test maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test remove(4)") {
        AVLTree.Remove(4);
        REQUIRE(AVLTree.Search(4) == nullptr);
        REQUIRE(AVLTree.Height() == 3);
        REQUIRE(AVLTree.Size() == 6);
      }
      THEN("Test clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; ++i) {
        AVLTree.Insert(i, 0);
      }
      THEN("Test size()") { REQUIRE(AVLTree.Size() == 10); }
      THEN("Test height()") { REQUIRE(AVLTree.Height() == 4); }
      THEN("Test maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test remove(3)") {
        AVLTree.Remove(3);
        REQUIRE(AVLTree.Search(3) == nullptr);
        REQUIRE(AVLTree.Height() == 4);
        REQUIRE(AVLTree.Size() == 9);
      }
      THEN("Test clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; --i) {
        AVLTree.Insert(i, 0);
      }
      THEN("Test size()") { REQUIRE(AVLTree.Size() == 10); }
      THEN("Test height()") { REQUIRE(AVLTree.Height() == 4); }
      THEN("Test maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test remove(6)") {
        AVLTree.Remove(6);
        REQUIRE(AVLTree.Search(6) == nullptr);
        REQUIRE(AVLTree.Height() == 4);
        REQUIRE(AVLTree.Size() == 9);
      }
      THEN("Test clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
  }
}