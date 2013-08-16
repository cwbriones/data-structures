#include "Heap.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    int nums[] = {19, 36, 3, 100, 17, 1};
    heap_sort(nums, 6);

    for (auto x : nums){
        std::cout << x << " ";
    }
    std::cout  << std::endl;
    return 0;
}
