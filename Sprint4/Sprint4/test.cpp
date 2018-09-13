
//#ifndef CATCH_CONFIG_RUNNER
//#define CATCH_CONFIG_RUNNER
#include "../../lib/catch.hpp"
#include "../../lib/michaelString.h"
#include "../../lib/michaelvectors.h"
#include "../../lib/linkedlist.h"
#include "../../lib/stack.h"
TEST_CASE("LinkedList class","[LinkedList]"){

    LinkedList<int> L;
    L.insert(1);
    L.insert(2);
    L.insert(3);
    L.insert(4);
    L.insert(5);

    SECTION("POP"){
        REQUIRE(L.pop() == 5);
        REQUIRE(L.pop() == 4);
        REQUIRE(L.pop() == 3);
        REQUIRE(L.pop() == 2);
        REQUIRE(L.pop() == 1);
    }

    SECTION("SEARCH"){

        REQUIRE(L.search(4) == true);
        REQUIRE(L.search(3) == true);
        REQUIRE(L.search(2) == true);
        REQUIRE(L.search(1) == true);
    }

}
TEST_CASE("Stack class", "[Stack]"){
    Stack<int> S;
    S.push(5);
    S.push(4);
    S.push(3);
    S.push(2);
    S.push(1);

    SECTION("POP and PEEK and ISEMPTY"){
        REQUIRE(S.peek() == 1);
        REQUIRE(S.pop() == 1);
        REQUIRE(S.peek() ==2);
        REQUIRE(S.pop() == 2);
        REQUIRE(S.peek() ==3);
        REQUIRE(S.pop() == 3);
        REQUIRE(S.peek() ==4);
        REQUIRE(S.pop() == 4);
        REQUIRE(S.peek() ==5);
        REQUIRE(S.pop() == 5);
        REQUIRE(S.isEmpty() == true);
    }
    SECTION("SEARCH"){

        REQUIRE(S.search(2) == true);
        REQUIRE(S.search(3) == true);
        REQUIRE(S.search(4) == true);
        REQUIRE(S.search(5) == true);
    }
}

TEST_CASE("michaelVector class", "[michaelVector]"){
    michaelVector<int> V;
        V.add(3);
        V.add(1);
        V.add(2);
        V.add(5);
        V.add(1000);
        V.add(-15);
     michaelVector<int> V2;

     SECTION("Assignment Operator"){ //operator to assign the values of one michaelVector to another
         V2 = V;
         REQUIRE(V[0] == V2[0]);
         REQUIRE(V[1] == V2[1]);
         REQUIRE(V[2] == V2[2]);
         REQUIRE(V[3] == V2[3]);
         REQUIRE(V[4] == V2[4]);
     }

    SECTION("Sort Function"){ //function to sort a michaelVector in ascending order
        V.sort(0);
        REQUIRE(V[0] < V[1]);
        REQUIRE(V[1] < V[2]);
        REQUIRE(V[2] < V[3]);
        REQUIRE(V[3] < V[4]);
        REQUIRE(V[4] < V[5]);
    }


    SECTION("Bracket Operator"){ //operator to return the specified value from the bracket of a michaelVector
        V.sort(0);
        REQUIRE(V[0] == -15);
        REQUIRE(V[1] == 1);
        REQUIRE(V[2] == 2);
        REQUIRE(V[3] == 3);
        REQUIRE(V[4] == 5);
        REQUIRE(V[5] == 1000);
    }

    SECTION("Search function"){ //function to search a michaelVector for a specified value
        REQUIRE(V.Search(1) == true);
        REQUIRE(V.Search(2) == true);
        REQUIRE(V.Search(3) == true);
        REQUIRE(V.Search(5) == true);
        REQUIRE(V.Search(1000) == true);
        REQUIRE(V.Search(-15) == true);

    }

    SECTION("Pop function"){ //function to remove the end value value from a michaelVector a return it
        V.sort(0);
        REQUIRE(V.pop() == 1000);
        REQUIRE(V.pop() == 5);
        REQUIRE(V.pop() == 3);
        REQUIRE(V.pop() == 2);
        REQUIRE(V.pop() == 1);
        REQUIRE(V.pop() == -15);
        REQUIRE(V.getLength() == 0);
    }


}

TEST_CASE("michaelString class", "[michaelString]"){


    michaelString s[10];
    s[0] = michaelString("testString");
    s[1] = michaelString("a test string");
    s[2] = michaelString("");
    s[3] = michaelString("THIS IS AN UPPERCASE STRING");
    s[4] = michaelString("this is an uppercase string");
    s[5] = michaelString("\n");
    s[6] = michaelString("");
    s[7] = michaelString("  split  split  split  ");
    s[8] = michaelString("                          ");
    s[9] = michaelString("testString");

    SECTION("Equality operators"){
        REQUIRE(s[0] == michaelString("testString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        michaelString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = michaelString("testString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = michaelString("\n");
        REQUIRE(str == s[5]);
    }


    SECTION("Greater than operator"){
        //REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("Size function"){
        REQUIRE(s[9].getLength() == 10);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].subString(0, 5) == "testS");
        REQUIRE(s[4].subString(0, 4) == "this");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].getWord(), "testString") == 0);
        REQUIRE(strcmp(s[2].getWord(), "") == 0);
    }
}
//#endif // TEST_H
