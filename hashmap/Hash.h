#ifndef HASH_H_
#define HASH_H_

#include <stddef.h>
#include <string>

template <typename Key>
struct Hash {
    Hash(){};
    size_t operator()(const Key& k) const;
};

template <>
struct Hash<int> {
    inline size_t operator()(const int& k) const { 
        return k & 0x7fffffff; 
    };
};

template <>
struct Hash<std::string> {
    size_t operator()(const std::string& k) const {
        int hash = 5381;

        for (auto& chr : k){
            hash = ((hash << 5) + hash) + chr;
        }
        return hash & 0x7fffffff;
    };
};

#endif // HASH_H_
