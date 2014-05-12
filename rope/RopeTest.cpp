#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Rope test

#include <boost/test/unit_test.hpp>
#include <iostream>

#include "Rope.h"

BOOST_AUTO_TEST_CASE(test_empty_rope) {
    Rope rope("");
}

BOOST_AUTO_TEST_CASE(test_rope_construction) {
    Rope rope("words words words");
}
// 
BOOST_AUTO_TEST_CASE(test_rope_length) {
    std::string str("words words words");
    Rope rope(str);

    BOOST_CHECK_EQUAL(str.size(), rope.size());
}

BOOST_AUTO_TEST_CASE(test_rope_to_str) {
    std::string str("this is a test of the rope.");
    Rope rope(str);

    BOOST_CHECK_EQUAL(str, rope.to_str());

    Rope rope2;
    BOOST_CHECK_EQUAL(rope2.to_str(), "");
}

BOOST_AUTO_TEST_CASE(test_rope_indexing) {
    std::string str("this is a test of the rope.");
    Rope rope(str);
    
    for (int i = 0; i < str.size(); ++i) {
        BOOST_CHECK_EQUAL(str[i], rope.at(i));
    }
}

BOOST_AUTO_TEST_CASE(test_rope_concat) {
    Rope rope1("this is a test of");
    Rope rope2(" concatenating ropes.");

    Rope rope3(rope1, rope2);
    BOOST_CHECK_EQUAL(
            "this is a test of concatenating ropes.",
            rope3.to_str());
}

// BOOST_AUTO_TEST_CASE(test_rope_split) {
// }
