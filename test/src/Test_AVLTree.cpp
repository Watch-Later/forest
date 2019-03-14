#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/AVLTree.hpp>

SCENARIO("Test AVL Tree") {
  GIVEN("An AVL Tree") {
    forest::AVLTree<int, int> AVLTree;
    WHEN("The AVL Tree is empty") {
      THEN("Test Size()") { REQUIRE(AVLTree.Size() == 0); }
      THEN("Test Height()") { REQUIRE(AVLTree.Height() == 0); }
      THEN("Test Maximum()") { REQUIRE(AVLTree.Maximum() == nullptr); }
      THEN("Test Minimum()") { REQUIRE(AVLTree.Minimum() == nullptr); }
      THEN("Test Search(555)") { REQUIRE(AVLTree.Search(555) == nullptr); }
      THEN("Test Clear()") {
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
      THEN("Test Size()") { REQUIRE(AVLTree.Size() == 7); }
      THEN("Test Height()") { REQUIRE(AVLTree.Height() == 3); }
      THEN("Test Maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 90);
      }
      THEN("Test Minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test Search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test Search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test Remove(4)") {
        AVLTree.Remove(4);
        REQUIRE(AVLTree.Search(4) == nullptr);
        REQUIRE(AVLTree.Height() == 3);
        REQUIRE(AVLTree.Size() == 6);
      }
      THEN("Test Clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in ascending order") {
      for (int i = 0; i < 10; ++i) {
        AVLTree.Insert(i, 0);
      }
      THEN("Test Size()") { REQUIRE(AVLTree.Size() == 10); }
      THEN("Test Height()") { REQUIRE(AVLTree.Height() == 4); }
      THEN("Test Maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test Minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test Search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test Search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test Remove(3)") {
        AVLTree.Remove(3);
        REQUIRE(AVLTree.Search(3) == nullptr);
        REQUIRE(AVLTree.Height() == 4);
        REQUIRE(AVLTree.Size() == 9);
      }
      THEN("Test Clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
    WHEN("Nodes are inserted in descending order") {
      for (int i = 9; i >= 0; --i) {
        AVLTree.Insert(i, 0);
      }
      THEN("Test Size()") { REQUIRE(AVLTree.Size() == 10); }
      THEN("Test Height()") { REQUIRE(AVLTree.Height() == 4); }
      THEN("Test Maximum()") {
        auto max = AVLTree.Maximum();
        REQUIRE(max != nullptr);
        REQUIRE(max->key == 9);
      }
      THEN("Test Minimum()") {
        auto min = AVLTree.Minimum();
        REQUIRE(min != nullptr);
        REQUIRE(min->key == 0);
      }
      THEN("Test Search(1337)") { REQUIRE(AVLTree.Search(1337) == nullptr); }
      THEN("Test Search(3)") {
        auto result = AVLTree.Search(3);
        REQUIRE(result != nullptr);
        REQUIRE(result->key == 3);
      }
      THEN("Test Remove(6)") {
        AVLTree.Remove(6);
        REQUIRE(AVLTree.Search(6) == nullptr);
        REQUIRE(AVLTree.Height() == 4);
        REQUIRE(AVLTree.Size() == 9);
      }
      THEN("Test Clear()") {
        AVLTree.Clear();
        REQUIRE(AVLTree.Height() == 0);
        REQUIRE(AVLTree.Size() == 0);
      }
    }
  }
}