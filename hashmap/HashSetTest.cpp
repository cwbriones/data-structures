#define BOOST_TEST_MODULE HashSet test
#include <iostream>
#include <string>

#include <boost/test/unit_test.hpp>

#include "HashSet.h"

BOOST_AUTO_TEST_CASE(ctor_test){
    HashSet<std::string> set1;

    HashSet<std::string> set2 = { "Dog", "Cat", "Monkey", 
        "Antelope", "Racoon", "Giraffe", "Lion" };
}

BOOST_AUTO_TEST_CASE(size_test){
}

BOOST_AUTO_TEST_CASE(put_test1){
    HashSet<std::string> set;
}

BOOST_AUTO_TEST_CASE(put_test2){
    HashSet<std::string> set;
}

BOOST_AUTO_TEST_CASE(duplicate_test){
    HashSet<std::string> string_set;

    string_set.put("Dog");
    string_set.put("Cat");
    string_set.put("Cat");

    BOOST_CHECK_EQUAL(string_set.size(), 2);

    HashSet<int> int_set;

    int_set.put(1);
    int_set.put(3);
    int_set.put(1);

    BOOST_CHECK_EQUAL(int_set.size(), 2);
}

BOOST_AUTO_TEST_CASE(rehash_test){
}

BOOST_AUTO_TEST_CASE(iteration_test){
}

BOOST_AUTO_TEST_CASE(contains_test){
}

BOOST_AUTO_TEST_CASE(clear_test){
}
