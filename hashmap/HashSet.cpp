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
    const int TEST_SIZE = 20;

    std::vector<std::string> test_strings;
    test_strings.reserve(TEST_SIZE);
    
    int string_id = 0;

    for (int i = 0; i < TEST_SIZE; i++){
        const char int_char = static_cast<char>(string_id + static_cast<int>('0'));
        const char alpha_char = static_cast<char>(string_id + static_cast<int>('a'));

        std::string item = "str_";
        item += alpha_char;
        item += int_char;

        test_strings.push_back(item);
        string_id++;
    }

    // test_strings now contains TEST_SIZE unique strings
    // assuming TEST_SIZE + (int)('a') < 256
    
    HashSet<std::string> set;
    for (auto str : test_strings){
        set.put(str);
    }

    BOOST_CHECK_EQUAL(set.size(), TEST_SIZE);
}

BOOST_AUTO_TEST_CASE(put_test1){
    HashSet<std::string> set;

    set.put("String1");
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
