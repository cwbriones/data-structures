#include "List.h"

#include <iostream>

int main(int argc, const char *argv[])
{
    List<int> list;
    for (int i = 1; i <= 10; i++){
        list.append(i);
    }
    list.reverse();
    list.remove(list.begin() + 1); // Removes 9
    list.remove(list.begin() + 2); // Removes 7

    // Should print 10 8 6 5 4 3 2 1
    for (auto x : list){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
