#include "Bloom.h"
#include <vector>
#include <iostream>

unsigned int sax_hash(std::string str){
    unsigned int h = 0;

    for (auto x : str){
        h ^= (h << 5) + (h >> 2) + (x);
    }
    return h;
}

unsigned int fnv_hash(std::string str){
    unsigned int h = 2166136261;
    for (auto x : str){
        h = (h * 16777619) ^ (x);
    }
    return h;
}

unsigned int oat_hash(std::string str){
    unsigned int h = 0;

    for (auto x : str) {
        h += x;
        h += (h << 10);
        h ^= (h >> 6);
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}

unsigned int jsw_hash(std::string str){
    unsigned int h = 0, g;

    for (auto x : str) {
       h = (h << 4) + x; 
       g = h & 0xf0000000L;

       if (g != 0){
           h ^= g >> 24;
       }
       h &= ~g;
    }
    return h;
}
 
int main(int argc, const char *argv[])
{
    std::vector< HashFunc_t > hashes = {
        sax_hash, fnv_hash, oat_hash, jsw_hash
    };
    Bloom<10000> bloom(hashes);

    bloom.add("Dog");
    bloom.add("Cat");

    std::cout << bloom.contains("Dog") << std::endl;
    std::cout << bloom.contains("Cat") << std::endl;
    std::cout << bloom.contains("Bird") << std::endl;
    return 0;
}
