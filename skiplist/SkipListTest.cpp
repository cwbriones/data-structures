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

BOOST_AUTO_TEST_CASE(contains_test1) {
    const int TEST_SIZE = 50;

    // std::vector<int> numbers(TEST_SIZE);
    // for (int i = 0; i < TEST_SIZE; i++){
    //     numbers[i] = 2 * i + 1;
    // }
    // std::random_shuffle(numbers.begin(), numbers.end());

    // SkipList<int> slist;
    // for (auto& x : numbers){
    //     slist.insert(x);
    // }

    // slist.insert(50);
    // BOOST_CHECK(slist.contains(50));
}

BOOST_AUTO_TEST_CASE(contains_test2) {
    // SkipList<int> slist;

    // slist.insert(10);
    // BOOST_CHECK(slist.contains(10));
    // slist.insert(15);
    // BOOST_CHECK(slist.contains(15));
    // slist.insert(7);
    // BOOST_CHECK(slist.contains(7));
    // slist.insert(20);
    // BOOST_CHECK(slist.contains(20));
}

BOOST_AUTO_TEST_CASE(index_address_test){
    SkipList<int> slist;

    const int TEST_SIZE = 20;

    for (int i = 0; i < 20; i++){
        slist.insert(i);
    }

    for (int i = 0; i < 20; i++){
        if (slist.at(i)){
            BOOST_CHECK_EQUAL(i, *slist.at(i));
        }
    }
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
