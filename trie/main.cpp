#include "Trie.h"
#include <iostream>

void print_result(int* result){
    if (result){
        std::cout << "Item: '" << *result << "' found in container." << std::endl;
    } else {
        std::cout << "Item not found." << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    Trie<int> trie;
    trie.put("She", 3);
    trie.put("Shells", -10);
    print_result(trie.get("She"));
    print_result(trie.get("Shells"));
    print_result(trie.get("Sells"));
    return 0;
}
