
#ifndef CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "michaelString.h"
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
#endif // TEST_H
