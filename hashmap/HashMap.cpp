#include <iostream>
#include <cassert>

#include "HashMap.h"

int main(int argc, const char *argv[])
{
    HashMap<std::string, int> map;
    map.put("Doggy", 15);
    std::cout << map.contains("Doggy") << std::endl;

    return 0;
}
