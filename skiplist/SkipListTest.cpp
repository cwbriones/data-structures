#define BOOST_TEST_MODULE SkipList test

#include <boost/test/unit_test.hpp>

#include "SkipList.h"
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <vector>
#include <algorithm>

/**
 * Generates a random integer in
 * the range [a, b]
 */
int rand_int(int a, int b){
    int n = b - a + 1;

    int x;
    int max_limit = RAND_MAX - n;
    while ((x = rand()) >= max_limit){}
    return a + x % n;
}

BOOST_AUTO_TEST_CASE(size_test) {
    const int TEST_SIZE = 50;

    std::vector<int> numbers(TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++){
        numbers[i] = 2 * i + 1;
    }
    std::random_shuffle(numbers.begin(), numbers.end());

    SkipList<int> slist;
    BOOST_CHECK(slist.empty());

    for (auto& x : numbers){
        slist.insert(x);
    }
    BOOST_CHECK_EQUAL(slist.size(), TEST_SIZE);
    BOOST_CHECK(!slist.empty());
}

BOOST_AUTO_TEST_CASE(range_based_iteration_test) {
    const int TEST_SIZE = 50;

    std::vector<int> numbers(TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++){
        numbers[i] = i;
    }
    std::random_shuffle(numbers.begin(), numbers.end());

    SkipList<int> slist;
    for (auto& x : numbers){
        slist.insert(x);
    }

    int j = 0;
    for (auto& i: slist){
        BOOST_CHECK_EQUAL(i, j++);
    }
}

BOOST_AUTO_TEST_CASE(contains_test) {
    const int TEST_SIZE = 10;

    std::vector<int> numbers(TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++){
        numbers[i] = 2 * i + 1;
    }
    std::random_shuffle(numbers.begin(), numbers.end());

    SkipList<int> slist;
    for (auto x : numbers){
        slist.insert(x);
    }

    for (auto x : numbers){
        BOOST_CHECK(slist.contains(x));
    }
}

BOOST_AUTO_TEST_CASE(index_address_test){
    SkipList<int> slist;

    const int TEST_SIZE = 20;

    for (int i = 0; i < TEST_SIZE; i++){
        slist.insert(i);
    }

    for (int i = 0; i < TEST_SIZE; i++){
        BOOST_CHECK_EQUAL(i, slist.at(i));
    }

}

BOOST_AUTO_TEST_CASE(index_out_of_range_test){
    
    SkipList<int> slist;

    BOOST_CHECK_THROW(slist.at(-1), std::out_of_range);
    BOOST_CHECK_THROW(slist.at(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(is_sorted_test){
    const int TEST_SIZE = 50;

    std::vector<int> numbers(TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++){
        numbers[i] = 2 * i + 1;
    }
    std::random_shuffle(numbers.begin(), numbers.end());

    SkipList<int> slist;
    for (auto& x : numbers){
        slist.insert(x);
    }

    int last = -1;
    for (auto& c: slist){
        BOOST_CHECK(c > last);
        last = c;
    }
}
