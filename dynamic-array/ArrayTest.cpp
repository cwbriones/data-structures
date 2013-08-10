#include "ArrayList.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    Array<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);
    array.push_back(4);
    array.push_back(5);

    for (int i = 0; i < array.size(); i++){
        std::cout << array[i] << std::endl;
    }
    array[2] = 10;
    for (int i = 0; i < array.size(); i++){
        std::cout << array[i] << std::endl;
    }
    return 0;
}
