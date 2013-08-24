#include "HashSet.h"

#include <string>
#include <iostream>

int main(int argc, const char *argv[])
{
    HashSet<std::string> set = { "Dog", "Cat", "Monkey", "Antelope", "Racoon", "Giraffe", "Lion" };
    std::cout << "There are " << set.size() << " items in the set: " << std::endl;
    for (auto item : set){
        std::cout << item << std::endl;
    }
    return 0;
}
