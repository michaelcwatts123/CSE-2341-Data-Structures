#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstring>
#include <chrono>

#include "catch.hpp"
#include "porter2_stemmer.h"
#include "hashtable.hpp"
#include "avltree.hpp"
#include "indexedterm.h"
#include "indexhandler.h"
#include "documentparser.h"

using namespace std;


TEST_CASE("AVL Tree") {

//    AVLTree<int> test0;
//    AVLTree<int> test1;
//    AVLTree<int> test2;
    AVLTree<IndexedTerm> test3;
    AVLTree<IndexedTerm> test4;
    AVLTree<IndexedTerm> test5;

//    test0.insert(55);
//    test0.insert(40);
//    test0.insert(70);

//    test1.insert(8);
//    test1.insert(7);
//    test1.insert(12);
//    test1.insert(3);
//    test1.insert(20);


    test3.insert(std::string("rdj"));
    test3.insert(std::string("syro"));
    test3.insert(std::string("ccai2"));
    test3.insert(std::string("drukqs"));
    test3.insert(std::string("selected"));

    test4.insert(std::string("foo"));
    test4.insert(std::string("bar"));
    test4.insert(std::string("quux"));
    test4.insert(std::string("baz"));
    test4.insert(std::string("qux"));


    SECTION("isEmpty") {
//        REQUIRE_FALSE(test0.isEmpty());
//        REQUIRE_FALSE(test1.isEmpty());
//        REQUIRE(test2.isEmpty());
        REQUIRE_FALSE(test3.isEmpty());
        REQUIRE_FALSE(test4.isEmpty());
        REQUIRE(test5.isEmpty());
    }


    SECTION("Get maxes and mins") {

//        REQUIRE(test0.findMax() == 70);
//        REQUIRE(test0.findMin() == 40);

//        REQUIRE(test1.findMax() == 20);
//        REQUIRE(test1.findMin() == 3);

        REQUIRE(test3.findMax() == std::string("syro"));
        REQUIRE(test3.findMin() == std::string("ccai2"));

        REQUIRE(test4.findMax() == std::string("qux"));
        REQUIRE(test4.findMin() == std::string("bar"));

    }


    SECTION("Make Empty") {
//        test0.makeEmpty();
//        REQUIRE(test0.isEmpty());

//        test1.makeEmpty();
//        REQUIRE(test1.isEmpty());

//        test2.makeEmpty();
//        REQUIRE(test2.isEmpty());

        test3.makeEmpty();
        REQUIRE(test3.isEmpty());

        test4.makeEmpty();
        REQUIRE(test4.isEmpty());

        test5.makeEmpty();
        REQUIRE(test5.isEmpty());
    }


    SECTION("Check for Membership") {

//        REQUIRE(test0.contains(55));
//        REQUIRE(test0.contains(40));
//        REQUIRE(test0.contains(70));
//        REQUIRE_FALSE(test0.contains(65));

//        REQUIRE(test1.contains(8));
//        REQUIRE(test1.contains(7));
//        REQUIRE(test1.contains(12));
//        REQUIRE(test1.contains(3));
//        REQUIRE(test1.contains(20));
//        REQUIRE_FALSE(test1.contains(9));

//        REQUIRE_FALSE(test2.contains(6));

        REQUIRE(test3.contains(std::string("selected")));
        REQUIRE(test3.contains(std::string("drukqs")));
        REQUIRE(test3.contains(std::string("ccai2")));
        REQUIRE(test3.contains(std::string("syro")));
        REQUIRE(test3.contains(std::string("rdj")));
        REQUIRE_FALSE(test3.contains(std::string("")));

        REQUIRE(test4.contains(std::string("foo")));
        REQUIRE(test4.contains(std::string("quux")));
        REQUIRE(test4.contains(std::string("qux")));
        REQUIRE(test4.contains(std::string("bar")));
        REQUIRE(test4.contains(std::string("baz")));
        REQUIRE_FALSE(test4.contains(std::string("foobar")));

    }


    SECTION("Searching") {


//        REQUIRE(test0.search(40).first == 40);
//        REQUIRE(test0.search(40).second == true);
//        REQUIRE(test0.search(85).first == 85);
//        REQUIRE(test0.search(85).second == false);

//        REQUIRE(test1.search(3).first == 3);
//        REQUIRE(test1.search(3).second == true);
//        REQUIRE(test1.search(80).first == 80);
//        REQUIRE(test1.search(80).second == false);

//        REQUIRE(test2.search(70).first == 70);
//        REQUIRE(test2.search(70).second == false);

        REQUIRE(test3.search(std::string("drukqs")).first == std::string("drukqs"));
        REQUIRE(test3.search(std::string("drukqs")).second == true);
        REQUIRE(test3.search(std::string("melodiesfrommars")).first == std::string("melodiesfrommars"));
        REQUIRE(test3.search(std::string("melodiesfrommars")).second == false);

        REQUIRE(test5.search(std::string("foobar")).first == std::string("foobar"));
        REQUIRE(test5.search(std::string("foobar")).second == false);

    }


    SECTION("Complex Insertions") {

//        cout << test1 << endl;
//        test1.insert(1);
//        cout << test1 << endl;
//        test1.insert(40);
//        cout << test1 << endl;

//        cout << test3 << endl;
        test3.insert(std::string("sergefenix"));
//        cout << test3 << endl;
        test3.insert(std::string("donkeyrhubarb"));
//        cout << test3 << endl;
    }


    SECTION("Copy Constructor and Assignment Op") {

//        AVLTree<int> copy1(test1);
//        cout << copy1 << endl;

        AVLTree<IndexedTerm> copy4 = test4;
//        cout << copy4 << endl;

        AVLTree<IndexedTerm> copy5 = test5;
        cout << copy5 << endl;
    }
}


TEST_CASE("Hash Table") {

    HashTable<IndexedTerm> test0(25);
    HashTable<IndexedTerm> test1(87);
    HashTable<IndexedTerm> test2(6);
    HashTable<IndexedTerm> test3(554);

    test0.insert(IndexedTerm("euler"));
    test0.insert(IndexedTerm("spivak", 137, 137, 137));
    test0.insert(IndexedTerm("gauss"));

    test1.insert(IndexedTerm("graham", 57, 6, 12));
    test1.insert(IndexedTerm("house"));
    test1.insert(IndexedTerm("caesar"));
    test1.insert(IndexedTerm("yesman", 4096, 2048, 1024));
    test1.insert(IndexedTerm("kimball"));
    test1.insert(IndexedTerm("courier"));

    test2.insert(IndexedTerm("T1"));
    test2.insert(IndexedTerm("T1.5", 606, 404, 2));
    test2.insert(IndexedTerm("T2"));
    test2.insert(IndexedTerm("T3"));
    test2.insert(IndexedTerm("T4"));
    test2.insert(IndexedTerm("T5", 27, 8, 9));
    test2.insert(IndexedTerm("T6"));


    SECTION("Is Empty") {

        REQUIRE_FALSE(test0.isEmpty());
        REQUIRE_FALSE(test1.isEmpty());
        REQUIRE_FALSE(test2.isEmpty());
        REQUIRE(test3.isEmpty());

    }


    SECTION("Insertions and Containment") {

        REQUIRE(test0.getNumElements() == 3);
        REQUIRE(test0.contains(IndexedTerm("euler")));
        REQUIRE(test0.contains(IndexedTerm("gauss")));
        REQUIRE(test0.contains(IndexedTerm("spivak")));
        REQUIRE_FALSE(test0.contains(IndexedTerm("hausdorff")));

        REQUIRE(test1.getNumElements() == 6);
        REQUIRE(test1.contains(IndexedTerm("graham")));
        REQUIRE(test1.contains(IndexedTerm("house")));
        REQUIRE(test1.contains(IndexedTerm("caesar")));
        REQUIRE(test1.contains(IndexedTerm("yesman")));
        REQUIRE(test1.contains(IndexedTerm("kimball")));
        REQUIRE(test1.contains(IndexedTerm("courier")));
        REQUIRE_FALSE(test1.contains(IndexedTerm("klein")));
        REQUIRE_FALSE(test1.contains(IndexedTerm("mobius")));

        REQUIRE(test2.getNumElements() == 7);
        REQUIRE(test2.contains(IndexedTerm("T1")));
        REQUIRE(test2.contains(IndexedTerm("T1.5")));
        REQUIRE(test2.contains(IndexedTerm("T2")));
        REQUIRE(test2.contains(IndexedTerm("T3")));
        REQUIRE(test2.contains(IndexedTerm("T4")));
        REQUIRE(test2.contains(IndexedTerm("T5")));
        REQUIRE(test2.contains(IndexedTerm("T6")));
        REQUIRE_FALSE(test2.contains(IndexedTerm("T2.5")));

        test1.insert(IndexedTerm("graham", 23, 18, 6));
        test1.insert(IndexedTerm("yesman", 4096, 12, 6));
        test1.insert(IndexedTerm("kimball", 18, 53, 68));

        test0.insert(IndexedTerm("spivak", 66, 55, 44));
        test0.insert(IndexedTerm("gauss", 12, 24, 36));

        REQUIRE(test1.search(IndexedTerm("graham")).first.isInQuestion(23));
        REQUIRE(test1.search(IndexedTerm("graham")).first.isInQuestion(57));
        REQUIRE(test1.search(IndexedTerm("graham")).first.getFrequency(23) == 18);
        REQUIRE(test1.search(IndexedTerm("graham")).first.getFrequency(57) == 6);
        REQUIRE(test1.search(IndexedTerm("graham")).first.isAtLocation(23, 6));
        REQUIRE(test1.search(IndexedTerm("graham")).first.isAtLocation(57, 12));

        REQUIRE(test1.search(IndexedTerm("yesman")).first.isInQuestion(4096));
        REQUIRE(test1.search(IndexedTerm("yesman")).first.getFrequency(4096) == 2060);
        REQUIRE(test1.search(IndexedTerm("yesman")).first.isAtLocation(4096, 6));
        REQUIRE(test1.search(IndexedTerm("yesman")).first.isAtLocation(4096, 1024));

        REQUIRE(test1.getNumElements() == 6);

        REQUIRE(test1.search(IndexedTerm("kimball")).first.isInQuestion(18));
        REQUIRE(test1.search(IndexedTerm("kimball")).first.getFrequency(18) == 53);
        REQUIRE(test1.search(IndexedTerm("kimball")).first.isAtLocation(18, 68));

        REQUIRE(test0.search(IndexedTerm("spivak")).first.isInQuestion(66));
        REQUIRE(test0.search(IndexedTerm("spivak")).first.isInQuestion(137));
        REQUIRE(test0.search(IndexedTerm("spivak")).first.getFrequency(66) == 55);
        REQUIRE(test0.search(IndexedTerm("spivak")).first.getFrequency(137) == 137);
        REQUIRE(test0.search(IndexedTerm("spivak")).first.isAtLocation(66, 44));
        REQUIRE(test0.search(IndexedTerm("spivak")).first.isAtLocation(137, 137));

        REQUIRE(test0.getNumElements() == 3);

    }


    SECTION("Searching and Subscripting") {

        REQUIRE(test0.search(IndexedTerm("spivak")).first.isInQuestion(137));
        REQUIRE(test0.search(IndexedTerm("spivak")).first.getFrequency(137) == 137);
        REQUIRE(test0.search(IndexedTerm("spivak")).first.isAtLocation(137, 137));

        REQUIRE_FALSE(test0.search(IndexedTerm("hausdorff")).second);

        REQUIRE(test1.search(IndexedTerm("graham")).first.isInQuestion(57));
        REQUIRE(test1.search(IndexedTerm("graham")).first.getFrequency(57) == 6);
        REQUIRE(test1.search(IndexedTerm("graham")).first.isAtLocation(57, 12));

        REQUIRE(test1.search(IndexedTerm("yesman")).first.isInQuestion(4096));
        REQUIRE(test1.search(IndexedTerm("yesman")).first.getFrequency(4096) == 2048);
        REQUIRE(test1.search(IndexedTerm("yesman")).first.isAtLocation(4096, 1024));

        REQUIRE_FALSE(test1.search(IndexedTerm(IndexedTerm("ron"))).second);

        REQUIRE(test2.search(IndexedTerm("T1.5")).first.isInQuestion(606));
        REQUIRE(test2.search(IndexedTerm("T1.5")).first.getFrequency(606) == 404);
        REQUIRE(test2.search(IndexedTerm("T1.5")).first.isAtLocation(606, 2));

        REQUIRE(test2.search(IndexedTerm("T5")).first.isInQuestion(27));
        REQUIRE(test2.search(IndexedTerm("T5")).first.getFrequency(27) == 8);
        REQUIRE(test2.search(IndexedTerm("T5")).first.isAtLocation(27, 9));

        REQUIRE_FALSE(test2.search(IndexedTerm("urysohn")).second);



        REQUIRE(test0[IndexedTerm("spivak")].first.isInQuestion(137));
        REQUIRE(test0[IndexedTerm("spivak")].first.getFrequency(137) == 137);
        REQUIRE(test0[IndexedTerm("spivak")].first.isAtLocation(137, 137));

        REQUIRE_FALSE(test0[IndexedTerm("hausdorff")].second);

        REQUIRE(test1[IndexedTerm("graham")].first.isInQuestion(57));
        REQUIRE(test1[IndexedTerm("graham")].first.getFrequency(57) == 6);
        REQUIRE(test1[IndexedTerm("graham")].first.isAtLocation(57, 12));

        REQUIRE(test1[IndexedTerm("yesman")].first.isInQuestion(4096));
        REQUIRE(test1[IndexedTerm("yesman")].first.getFrequency(4096) == 2048);
        REQUIRE(test1[IndexedTerm("yesman")].first.isAtLocation(4096, 1024));

        REQUIRE_FALSE(test1[IndexedTerm(IndexedTerm("ron"))].second);

        REQUIRE(test2[IndexedTerm("T1.5")].first.isInQuestion(606));
        REQUIRE(test2[IndexedTerm("T1.5")].first.getFrequency(606) == 404);
        REQUIRE(test2[IndexedTerm("T1.5")].first.isAtLocation(606, 2));

        REQUIRE(test2[IndexedTerm("T5")].first.isInQuestion(27));
        REQUIRE(test2[IndexedTerm("T5")].first.getFrequency(27) == 8);
        REQUIRE(test2[IndexedTerm("T5")].first.isAtLocation(27, 9));

        REQUIRE_FALSE(test2[IndexedTerm("urysohn")].second);
    }


    SECTION("Resizing") {

//        std::cout << test2 << std::endl;

        for(int i=0; i<20; i++) {
            char ins = '0' + i;
            test2.insert(IndexedTerm(std::string(1,ins)));
        }

        REQUIRE(test2.getNumElements() == 27);

//        std::cout << test2 << std::endl;
    }


    SECTION("Make Empty") {

        test0.makeEmpty();
        test1.makeEmpty();
        test2.makeEmpty();
        test3.makeEmpty();

        REQUIRE(test0.isEmpty());
        REQUIRE(test1.isEmpty());
        REQUIRE(test2.isEmpty());
        REQUIRE(test3.isEmpty());

    }

}


TEST_CASE("Indexed Terms") {


    IndexedTerm test0(std::string("alito"));
    IndexedTerm test1(std::string("sotomayor"));
    IndexedTerm test2(std::string("kagan"), 453157, 25, 83);
    IndexedTerm test3(std::string("gorsuch"), 8675309, 42, 75);
    IndexedTerm test4;


    SECTION("Constructor") {

        REQUIRE(test0.getTerm() == "alito");
        REQUIRE(test1.getTerm() == "sotomayor");
        REQUIRE(test2.getTerm() == "kagan");
        REQUIRE(test3.getTerm() == "gorsuch");
        REQUIRE(test4.getTerm() == "");

        REQUIRE(test0.isEmpty());
        REQUIRE(test1.isEmpty());
        REQUIRE_FALSE(test2.isEmpty());
        REQUIRE_FALSE(test3.isEmpty());
        REQUIRE(test4.isEmpty());

        REQUIRE(test2.getFrequency(453157) == 25);
        REQUIRE(test3.getFrequency(8675309) == 42);
        REQUIRE(test2.getFrequency(891) == 0);
    }


    SECTION("Equality Operators") {

        REQUIRE(test0 == IndexedTerm("alito"));
        REQUIRE(test1 == IndexedTerm("sotomayor"));
        REQUIRE(test2 == IndexedTerm("kagan"));
        REQUIRE(test3 == IndexedTerm("gorsuch"));
        REQUIRE(test4 == IndexedTerm(""));
    }


    SECTION("Addition Assignment") {

        test0 += IndexedTerm(std::string("alito"), 58, 256, 67);
        test0 += IndexedTerm(std::string("alito"), 58, 512, 53);
        test0 += IndexedTerm(std::string("alito"), 512, 58, 83);

        REQUIRE(test0.getFrequency(58) == 768);
        REQUIRE(test0.getFrequency(512) == 58);

        REQUIRE(test0.getFrequency(8916) == 0);

        REQUIRE(test0.getFrequency(58) == 768);
        REQUIRE(test0.getLocations(58)[0] == 67);
        REQUIRE(test0.getLocations(58)[1] == 53);
        REQUIRE(test0.getFrequency(75) == 0);

        test2 += IndexedTerm(std::string("kagan"), 812, 24, 57);
        REQUIRE_THROWS(test2 += IndexedTerm(std::string("sotomayor"), 212, 420, 6));

        REQUIRE(test2.getFrequency(812) == 24);

        REQUIRE(test2.getFrequency(453157) == 25);
        REQUIRE(test2.getLocations(453157)[0] == 83);
        REQUIRE(test2.getLocations(453).empty());

        test3 += IndexedTerm(std::string("gorsuch"), 67, 51, 86);
        test3 += IndexedTerm(std::string("gorsuch"), 198354, 65, 43);
        test3 += IndexedTerm(std::string("gorsuch"), 8675309, 47, 29);

        REQUIRE(test3.getFrequency(8675309) == 89);
        REQUIRE(test3.getLocations(8675309)[0] == 75);
        REQUIRE(test3.getLocations(8675309)[1] == 29);
        REQUIRE(test3.getLocations(8675309).size() == 2);
        REQUIRE(test3.getFrequency(67) == 51);        
        REQUIRE(test3.getLocations(198354)[0] == 43);
        REQUIRE(test3.getLocations(198354).size() == 1);
        REQUIRE(test3.getFrequency(198354) == 65);
        REQUIRE(test3.getLocations(67)[0] == 86);
        REQUIRE(test3.getLocations(67).size() == 1);
        REQUIRE(test3.getLocations(1986153).empty());
    }


    SECTION("Adding and Removing Quantities")   {

        test2.addFrequency(453157, 15);
        REQUIRE(test2.getFrequency(453157) == 40);
        test2.addLocation(453157, 480);
        REQUIRE(test2.getLocations(453157).size() == 2);
        REQUIRE(test2.isInQuestion(453157));
        REQUIRE(test2.isAtLocation(453157, 83));
        REQUIRE_FALSE(test2.isInQuestion(628));

        test2.addQuestion(628);
        REQUIRE(test2.getFrequency(628) == 0);
        REQUIRE(test2.isInQuestion(628));

        test2.addFrequency(628, 45);
        REQUIRE(test2.getFrequency(628) == 45);
        REQUIRE(test2.getLocations(628).size() == 0);

        test2.addLocation(628, 456);
        REQUIRE(test2.isAtLocation(628, 456));
        REQUIRE(test2.getLocations(628).size() == 1);

        test2.removeLocation(628, 456);
        REQUIRE_FALSE(test2.isAtLocation(628, 456));
        REQUIRE(test2.getLocations(628).size() == 0);

        test2.removeLocation(453157, 83);
        REQUIRE(test2.getLocations(453157).size() == 1);
        REQUIRE_THROWS(test2.addFrequency(589, 45));

        test2.removeQuestion(628);
        REQUIRE_THROWS(test2.addLocation(628, 74));
        REQUIRE(test2.getFrequency(628) == 0);


        test0.addQuestion(576);
        REQUIRE(test0.isInQuestion(576));
        REQUIRE(test0.getFrequency(576) == 0);
        REQUIRE(test0.getLocations(576).size() == 0);

        test0.addFrequency(576, 55);
        REQUIRE(test0.getFrequency(576) == 55);
        test0.addFrequency(576, 64);
        REQUIRE(test0.getFrequency(576) == 119);

        test0.addLocation(576, 212);
        REQUIRE(test0.isAtLocation(576, 212));
        REQUIRE_FALSE(test0.isAtLocation(576, 818));

        test0.addLocation(576, 818);
        REQUIRE(test0.isAtLocation(576, 818));
        REQUIRE_THROWS(test0.addLocation(8888, 44));

        test0.removeLocation(576, 818);
        REQUIRE_FALSE(test0.isAtLocation(576, 818));

        test0.removeQuestion(576);
        REQUIRE(test0.getFrequency(576) == 0);
        REQUIRE_THROWS(test0.addFrequency(576, 1));
        REQUIRE_THROWS(test0.addLocation(576, 3));
        REQUIRE_FALSE(test0.isInQuestion(576));
        REQUIRE_THROWS(test0.isAtLocation(576, 4));
    }


    SECTION("Getting Question IDs") {

        test1.addQuestion(8913);
        test1.addQuestion(11111);
        test1.addQuestion(88795);
        test1.removeQuestion(8913);

        std::set<int> questions1 = test1.getQuestionIds();
        std::set<int> questions0 = test0.getQuestionIds();

        REQUIRE(std::find(questions1.begin(), questions1.end(), 11111) != questions1.end());
        REQUIRE(std::find(questions1.begin(), questions1.end(), 88795) != questions1.end());
        REQUIRE(std::find(questions1.begin(), questions1.end(), 8913) == questions1.end());
        REQUIRE(std::find(questions1.begin(), questions1.end(), 156) == questions1.end());

        REQUIRE(std::find(questions0.begin(), questions0.end(), 189) == questions0.end());
        REQUIRE(std::find(questions0.begin(), questions0.end(), 453157) == questions0.end());

    }
}


TEST_CASE("Index Handler") {

    IndexHandler testAvl("avl");
    IndexHandler testHash("hash");

    testAvl.addToIndex("function", 812, 10, 27);
    testAvl.addToIndex("abstract", 286, 5, 68);
    testAvl.addToIndex("topolog", 420, 8, 12);
    testAvl.addToIndex("abstract", 286, 15, 126);
    testAvl.addToIndex("abstract", 186, 10, 50589335);

    testAvl.setNumQuestions(4);

    testHash.addToIndex("function", 812, 10, 27);
    testHash.addToIndex("abstract", 286, 5, 68);
    testHash.addToIndex("topolog", 420, 8, 12);
    testHash.addToIndex("abstract", 286, 15, 126);
    testHash.addToIndex("abstract", 186, 10, 50589335);

    testHash.setNumQuestions(4);


    SECTION("Adding things to the Index") {

        REQUIRE(testHash.searchIndex("abstract").second);
        REQUIRE(testHash.searchIndex("function").second);
        REQUIRE(testHash.searchIndex("topolog").second);

        REQUIRE(testAvl.searchIndex("abstract").second);
        REQUIRE(testAvl.searchIndex("function").second);
        REQUIRE(testAvl.searchIndex("topolog").second);

    }


    SECTION("Searching for things in the index") {

        REQUIRE(testAvl.searchIndex("abstract").second);
        REQUIRE(testAvl.searchIndex("abstract").first.getFrequency(286) == 20);
        REQUIRE(testAvl.searchIndex("abstract").first.getFrequency(186) == 10);

        REQUIRE(testAvl.searchIndex("function").second);
        REQUIRE(testAvl.searchIndex("function").first.getFrequency(812) == 10);

        REQUIRE(testAvl.searchIndex("topolog").second);
        REQUIRE(testAvl.searchIndex("topolog").first.getFrequency(420) == 8);
      

        REQUIRE(testHash.searchIndex("abstract").second);
        REQUIRE(testHash.searchIndex("abstract").first.getFrequency(286) == 20);
        REQUIRE(testHash.searchIndex("abstract").first.getFrequency(186) == 10);

        REQUIRE(testHash.searchIndex("function").second);
        REQUIRE(testHash.searchIndex("function").first.getFrequency(812) == 10);

        REQUIRE(testHash.searchIndex("topolog").second);
        REQUIRE(testHash.searchIndex("topolog").first.getFrequency(420) == 8);
    }


    SECTION("Writing to and reading from disk") {

        testAvl.writeToDisk();

        IndexHandler testCopy("avl");

        testCopy.readFromDisk();

        REQUIRE(testCopy.searchIndex("abstract").second);
        REQUIRE(testCopy.searchIndex("function").second);
        REQUIRE(testCopy.searchIndex("topolog").second);

        REQUIRE(testCopy.searchIndex("abstract").first.getFrequency(286) == 20);
        REQUIRE(testCopy.searchIndex("abstract").first.getFrequency(186) == 10);
        REQUIRE(testCopy.searchIndex("topolog").first.getFrequency(420) == 8);
        REQUIRE(testCopy.searchIndex("function").first.getFrequency(812) == 10);

        REQUIRE(testCopy.searchIndex("topolog").first.isAtLocation(420, 12));
        REQUIRE(testCopy.searchIndex("abstract").first.isAtLocation(286, 68));
        REQUIRE(testCopy.searchIndex("abstract").first.isAtLocation(186, 50589335));
        REQUIRE(testCopy.searchIndex("abstract").first.isAtLocation(286, 126));
        REQUIRE(testCopy.searchIndex("function").first.isAtLocation(812, 27));
      
        testHash.writeToDisk();

        IndexHandler hashCopy("hash");

        hashCopy.readFromDisk();

        REQUIRE(hashCopy.searchIndex("abstract").second);
        REQUIRE(hashCopy.searchIndex("function").second);
        REQUIRE(hashCopy.searchIndex("topolog").second);

        REQUIRE(hashCopy.searchIndex("abstract").first.getFrequency(286) == 20);
        REQUIRE(hashCopy.searchIndex("abstract").first.getFrequency(186) == 10);
        REQUIRE(hashCopy.searchIndex("topolog").first.getFrequency(420) == 8);
        REQUIRE(hashCopy.searchIndex("function").first.getFrequency(812) == 10);

        REQUIRE(hashCopy.searchIndex("topolog").first.isAtLocation(420, 12));
        REQUIRE(hashCopy.searchIndex("abstract").first.isAtLocation(286, 68));
        REQUIRE(hashCopy.searchIndex("abstract").first.isAtLocation(186, 50589335));
        REQUIRE(hashCopy.searchIndex("abstract").first.isAtLocation(286, 126));
        REQUIRE(hashCopy.searchIndex("function").first.isAtLocation(812, 27));
    }

}


TEST_CASE("Speed tests") {


    SECTION("Parsing and Indexing the Corpus") {

        /*
         * Current best parse/index time:           6:20
         * Current best parse/index/persist time:   7:33
         */


        IndexHandler ih("avl");
        DocumentParser d(&ih);
        d.loadStopWords("../stop_words.txt");

        time_t start_time = time(NULL);

        d.parse("2008-questions.csv");
        cout << "Parsed 2008 Questions." << endl;
        d.parse("2008-tags.csv");
        cout << "Parsed 2008 Tags." << endl;

        std::cout << "Parsing the 2008 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        auto search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        auto search_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2009-questions.csv");
        cout << "Parsed 2009 Questions." << endl;
        d.parse("2009-tags.csv");
        cout << "Parsed 2009 Tags." << endl;

        std::cout << "Parsing the 2009 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2010-questions.csv");
        cout << "Parsed 2010 Questions." << endl;
        d.parse("2010-tags.csv");
        cout << "Parsed 2010 Tags." << endl;

        std::cout << "Parsing the 2010 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2011-questions.csv");
        cout << "Parsed 2011 Questions." << endl;
        d.parse("2011-tags.csv");
        cout << "Parsed 2011 Tags." << endl;

        std::cout << "Parsing the 2011 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2012-questions.csv");
        cout << "Parsed 2012 Questions." << endl;
        d.parse("2012-tags.csv");
        cout << "Parsed 2012 Tags." << endl;

        std::cout << "Parsing the 2012 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2013-questions.csv");
        cout << "Parsed 2013 Questions." << endl;
        d.parse("2013-tags.csv");
        cout << "Parsed 2013 Tags." << endl;

        std::cout << "Parsing the 2013 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2014-questions.csv");
        cout << "Parsed 2014 Questions." << endl;
        d.parse("2014-tags.csv");
        cout << "Parsed 2014 Tags." << endl;

        std::cout << "Parsing the 2014 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2015-questions.csv");
        cout << "Parsed 2015 Questions." << endl;
        d.parse("2015-tags.csv");
        cout << "Parsed 2015 Tags." << endl;

        std::cout << "Parsing the 2015 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        d.parse("2016-questions.csv");
        cout << "Parsed 2016 Questions." << endl;
        d.parse("2016-tags.csv");
        cout << "Parsed 2016 Tags." << endl;

        std::cout << "Parsing the 2016 data took " << difftime(time(NULL), start_time) << " seconds for " << ih.getNumTerms() << " terms." << std::endl;

        search_start = std::chrono::high_resolution_clock::now();
        ih.searchIndex("api");
        search_end = std::chrono::high_resolution_clock::now();
        time_cost = search_end-search_start;
        std::cout << "At " << ih.getNumTerms() << " objects in the index, searching takes " << std::to_string(time_cost.count()) << " seconds." << std::endl;

        ih.writeToDisk();

        ih.updateTopFifty();
        std::vector<std::string> tops = ih.getTopFifty();

        std::ostream_iterator<std::string> out(std::cout, "\n");
        std::copy(tops.begin(), tops.end(), out);
    }


    SECTION("IndexedTerm") {

        IndexedTerm speedyboi("Gotta go fast.");
        int termLimit = 10000000;
        int instanceLimit = 10000;

        /*
        for(int i=1; i<termLimit; i++) {
            speedyboi += IndexedTerm("Gotta go fast.", i, i, i);
            speedyboi.appendData(i,i,i);
        }

        for(int i = 1; i < termLimit; i++) {
            for(int j=1; j < instanceLimit; j++) {
                speedyboi += IndexedTerm("Gotta go fast.", i, j, j);
            }
        }
        */
    }

}
