#ifndef BLOOM_H
#define BLOOM_H

#include <bitset>
#include <functional>
#include <vector>
#include <string>

typedef std::function<unsigned int (std::string)> HashFunc_t;

template <int size>
class Bloom {
public:
    Bloom(std::vector<HashFunc_t>);
    void add(std::string);
    bool contains(std::string);
    void clear();
private:
    int size_ = size;
    std::bitset<size> bits_;
    std::vector<HashFunc_t> hashes_;
};

template <int size>
Bloom<size>::Bloom(std::vector<HashFunc_t> hashes) : hashes_(hashes) {}

template <int size>
void Bloom<size>::add(std::string str){
    for (auto f : hashes_){
        bits_[ f(str) % size_ ] = true;
    }
    return;
}

template <int size>
bool Bloom<size>::contains(std::string str){
    for (auto f : hashes_){
        if (!bits_[ f(str) % size_ ]){
            return false;
        }
    }
    return true;
}

template <int size>
void Bloom<size>::clear(){
    bits_.reset();
}

#endif // BLOOM_H
