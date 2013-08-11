#include "Trie.h"
#include <iostream>

template <class T>
void print_result(T* result){
    if (result){
        std::cout << "Item: '" << *result << "' found in container." << std::endl;
    } else {
        std::cout << "Item not found." << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    Trie<float> trie;
    trie.put("She", 1.5f);
    trie.put("Shells", -10.1f);
    print_result(trie.get("She"));
    print_result(trie.get("Shells"));
    print_result(trie.get("Sells"));
    trie.clear();
    return 0;
}
