#include <string>
#include <iostream>
#include "HashSet.h"

int main(int argc, const char *argv[])
{
    HashSet<std::string> set = { "Dog", "Cat", "Monkey", "Antelope", "Racoon", "Giraffe", "Lion" };
    std::cout << set.size() << std::endl;
    for (auto item : set){
        std::cout << item << std::endl;
    }
    return 0;
}
