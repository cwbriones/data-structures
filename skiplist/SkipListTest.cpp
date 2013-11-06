#include "unit_test.h"
#include "SkipList.h"
#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cassert>

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

unittest {
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
    assert(slist.size() == TEST_SIZE);

    std::cout << "Size test passed." << std::endl;
}

unittest {
    SkipList<int> items;

    items.insert(10);
    assert(items.contains(10));
    items.insert(15);
    assert(items.contains(15));
    items.insert(7);
    assert(items.contains(7));
    items.insert(20);
    assert(items.contains(20));

    std::cout << "Sanity check contains test passed." << std::endl;
}

unittest {
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
        assert(i == j++);
    }
    std::cout << "Range-based iteration test passed." << std::endl;
}

unittest {
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

    slist.insert(50);
    assert(slist.contains(50));

    std::cout << "Contains test passed." << std::endl;
}

unittest {
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
        assert(c > last);
        last = c;
    }

    std::cout << "Sorted test passed." << std::endl;
}

int main(int argc, const char *argv[])
{
    std::srand(static_cast<int>(time(0)));

    return 0;
}
