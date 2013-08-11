#include "RBTree.h"

#include <cassert>
#include <iostream>
#include <string>

int main(int argc, const char *argv[])
{
    RBTree<std::string, int> tree = { 
        {"Dog", 1}, {"Cat", 2}, {"Monkey", 3}, {"Racoon", 72}, {"Antelope", 8}};

    return 0;
}
