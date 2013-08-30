#include "Heap.h"

#include <iostream>
#include <string>

int main(int argc, const char *argv[])
{
    std::string items[] = {"Dog", "Cat", "Parrot", "Monkey"};
    MinHeap<std::string> heap(items, sizeof(items)/sizeof(items[0]));

    while (!heap.is_empty()){
        std::cout << heap.pop_min() << std::endl;
    }

    return 0;
}
