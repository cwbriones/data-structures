#include "SkipList.h"
#include <iostream>

#include <cstdlib>
#include <ctime>
#include <cassert>

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

int main(int argc, const char *argv[])
{
    std::srand(static_cast<int>(time(0)));

    SkipList<int> slist;
    for (int i = 0; i < 50; i++){
        slist.insert( rand_int(1, 1000) );
    }
    slist.insert(57);
    assert(slist.contains(57));

    for (auto x : slist){
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
