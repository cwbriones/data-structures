#include <iostream>
#include <cassert>

#include "HashMap.h"

int main(int argc, const char *argv[])
{
    HashMap<std::string, int> map = { {"Doggy", 15}, {"Cat", 10}, {"Frog", 20} };

    for (auto iter = map.begin(); iter != map.end(); iter++){
        std::cout << (*iter).second << std::endl;
    }

    return 0;
}
