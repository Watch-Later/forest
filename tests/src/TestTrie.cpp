#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <forest/Trie.hpp>
#include <vector>
#include <algorithm>

SCENARIO("Empty Trie Tests") {
  GIVEN("An empty Trie") {
    THEN("Test for multibyte characters"){
        forest::Trie<char16_t> trie;
        REQUIRE(trie.size() == 0);

        trie.insert(u"");

        REQUIRE(trie.size() == 0);
        REQUIRE(trie.search(u"") == false);
        REQUIRE(trie.search(u"computer") == false);
        REQUIRE(trie.search(u" ") == false);
        REQUIRE(trie.remove(u"Computer") == false);

        trie.insert(u"");
        REQUIRE(trie.remove(u"") == false);
        REQUIRE(trie.size() == 0);
    }

    THEN("Test for unicode characters"){
        forest::Trie<char> trie;
        REQUIRE(trie.size() == 0);
        trie.insert("");

        REQUIRE(trie.size() == 0);
        REQUIRE(trie.search("") == false);
        REQUIRE(trie.search("computer") == false);
        REQUIRE(trie.search(" ") == false);
        REQUIRE(trie.remove("Computer") == false);
        trie.insert("");
        REQUIRE(trie.remove("") == false);
        REQUIRE(trie.size() == 0);
    }
   
  }
}

SCENARIO("Test Insert/Search methods in Trie Container") {
  GIVEN("An empty Trie") {
    forest::Trie<char16_t> trie;
    REQUIRE(trie.search(u"computer") == false);
    REQUIRE(trie.search(u" ") == false);
    REQUIRE(trie.search(u" Science ") == false);
    REQUIRE(trie.size() == 0);

    WHEN("I insert a few words"){
        trie.insert(u"Chemical");
        trie.insert(u"Computer");
        trie.insert(u"Computer");
        trie.insert(u"Computer Science");
        trie.insert(u"Computer Engineering");

        AND_THEN("Size Should be Number of Unique Words after Insertion"){
            REQUIRE(trie.size() == 4);
        }
        
        AND_THEN("Search Should work for Existing Words"){
            REQUIRE(trie.search(u"Chemical") == true);
            REQUIRE(trie.search(u"ChemicaL") == false);
            REQUIRE(trie.search(u"computer") == false);
            REQUIRE(trie.search(u"Computer") == true);
            REQUIRE(trie.search(u"Computer Engineering") == true);
            REQUIRE(trie.search(u"Computer Engineer") == false);
            REQUIRE(trie.search(u"Mechanical") == false);
            REQUIRE(trie.search(u"Computer Science") == true);
        }     
        }        
    }
  }

SCENARIO("Test Remove method in Trie Container") {

    forest::Trie<char16_t> trie;
    REQUIRE(trie.size() == 0);
    trie.insert(u"Chemical");
    trie.insert(u"Computer");
    trie.insert(u"Computer Science");
    trie.insert(u"Computer Engineering");

    GIVEN("A Partially Filled Trie and a Few Words are Removed"){
        REQUIRE(trie.remove(u"Computer Science") == true);
        REQUIRE(trie.remove(u"computer ") == false);
        REQUIRE(trie.remove(u"Computer") == true);
        REQUIRE(trie.remove(u"Computer Science") == false);
        REQUIRE(trie.remove(u"Computer Networking") == false);

        AND_THEN("Size Should be Number of Unique Words after Insertion"){
            REQUIRE(trie.size() == 2);
        }
        
        AND_THEN("Search Should only work for Existing Words"){
            REQUIRE(trie.search(u"Chemical") == true);
            REQUIRE(trie.search(u"Computer") == false);
            REQUIRE(trie.search(u"Computer Engineering") == true);
            REQUIRE(trie.search(u"Computer Science") == false);
        } 
    }
 
    GIVEN("A Partially Filled Trie and inserts/remove statements are mixed in"){
        REQUIRE(trie.remove(u"Computer Science") == true);
        trie.insert(u"Computer-Science");
        REQUIRE(trie.remove(u"Computer") == true);
        trie.insert(u"Computer Networking");

        AND_THEN("Size should again refelct number of deleted words"){
            REQUIRE(trie.size() == 4);
        }

        AND_THEN("Search One Last time"){
            REQUIRE(trie.search(u"Computer Engineering") == true);
            REQUIRE(trie.search(u"Computer-Science") == true);
            REQUIRE(trie.search(u"Computer Networking") == true);
            REQUIRE(trie.search(u"Computer Science") == false);
            REQUIRE(trie.search(u"Computer Engineer") == false);
            REQUIRE(trie.search(u"Computer") == false);
            REQUIRE(trie.search(u"Computer Networkin") == false);     
        }
    }         
}     

SCENARIO("Testing Predict Method of Trie Container") {

    forest::Trie<char16_t> trie;
    trie.insert(u"Chemical");
    trie.insert(u"Computer");
    trie.insert(u"computer modelling");
    trie.insert(u"Computer Science");
    trie.insert(u"Computer Engineering");
    trie.insert(u"Computer Networking");
    trie.insert(u"Computer Architecture");

    GIVEN("A Partially filled trie"){

        AND_THEN("Test for the size a Prefix with no Entries"){
            auto vec = trie.predict(u"Electrical");
            REQUIRE(vec.size() == 0);
        }
        
        AND_THEN("Test for Size and Contents of the Container => General Case"){

            std::vector<std::basic_string<char16_t>> test_vec{u"Computer",
                                                              u"Computer Architecture", 
                                                              u"Computer Engineering", 
                                                              u"Computer Networking", 
                                                              u"Computer Science"};
            auto vec = trie.predict(u"Comp");
            REQUIRE(vec.size() == test_vec.size());
            std::sort(vec.begin(), vec.end());
            REQUIRE(std::equal(vec.begin(), vec.end(), test_vec.begin()));  
        } 

        AND_THEN("Test for Size and Contents of the Container => General Case"){

            std::vector<std::basic_string<char16_t>> test_vec{u"Chemical",
                                                              u"Computer",
                                                              u"Computer Architecture", 
                                                              u"Computer Engineering", 
                                                              u"Computer Networking", 
                                                              u"Computer Science"};
            auto vec = trie.predict(u"C");
            REQUIRE(vec.size() == test_vec.size());
            std::sort(vec.begin(), vec.end());
            REQUIRE(std::equal(vec.begin(), vec.end(), test_vec.begin()));
        } 

        AND_THEN("Test for Size and Contents of the Container => Special Case: Input Prefix Should not be returned, even if its a legit word"){
            
            std::vector<std::basic_string<char16_t>> test_vec{u"Computer Architecture", 
                                                              u"Computer Engineering", 
                                                              u"Computer Networking", 
                                                              u"Computer Science"};
            auto vec = trie.predict(u"Computer");
            REQUIRE(vec.size() == test_vec.size());
            std::sort(vec.begin(), vec.end());
            REQUIRE(std::equal(vec.begin(), vec.end(), test_vec.begin()));
        }

        AND_THEN("Test for Size and Contents of the Container => Special Case: Case Sensitivity is Tested"){
            auto vec = trie.predict(u"c");
            REQUIRE(vec.size() == 1); 
            REQUIRE(vec[0] == u"computer modelling");
        }        
    }
} 