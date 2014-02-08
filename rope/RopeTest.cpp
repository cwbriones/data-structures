#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Rope test

#include <boost/test/unit_test.hpp>

#include "Rope.h"

BOOST_AUTO_TEST_CASE(test_empty_rope) {
    Rope rope("");
}

BOOST_AUTO_TEST_CASE(test_rope_construction) {
    Rope rope("words words words");
}
