#include <iostream>
#include <cassert>

#include "HashMap.h"

int main(int argc, const char *argv[])
{
    HashMap<std::string, int> map;
    map.put("Doggy", 15);
    if (map.contains("Doggy")){
        std::cout << map.get("Doggy") << std::endl;
    }

    return 0;
}
