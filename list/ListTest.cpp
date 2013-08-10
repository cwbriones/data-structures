#include "List.h"

#include <iostream>

int main(int argc, const char *argv[])
{
    List<int> list;
    for (int i = 1; i <= 10; i++){
        list.append(i);
    }

    for (auto x : list){
        std::cout << x << std::endl;
    }

    return 0;
}
