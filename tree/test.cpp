#include "RBTree.h"

#include <cassert>
#include <string>

int main(int argc, const char *argv[])
{
    RBTree<std::string, int> tree;
    tree.put("Dog", 1);
    tree.put("Cat", 2);
    tree.put("Monkey", 3);
    tree.put("Racoon", 72);
    tree.put("Antelope", 8);
    int i = 0;

    std::cout << "[";
    for (auto iter = tree.begin(); iter != tree.end(); ++iter){
        std::cout << (*iter).first << ", ";
    }
    std::cout << "]" << std::endl;

    return 0;
}
