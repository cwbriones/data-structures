#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <vector>
#include <string>
#include <functional>

#include "Hash.h"

template <class Key, class Value>
struct Pair {
    Key first;
    Value second;
};

// Hash implemented with linear probing
template <typename Key, typename Value>
class HashMap {
public:
    HashMap() : keys_(m_, nullptr), values_(m_, nullptr) {};

    ~HashMap(){
        for (int i = 0; i < m_; i++){
            if (keys_[i]){
                delete keys_[i];
                delete values_[i];
            }
        }
    }

    void put(Key key, Value value){
        if (n_ >= m_/2){
            resize(m_ * 2);
        }

        int i = hashcode(key) % m_;
        for(; keys_[i]; i = (i + 1) % m_){
            if (*(keys_[i]) == key){
                *values_[i] = Value(value);
                return;
            }
        }
        keys_[i] = new Key(key);
        values_[i] = new Value(value);
        n_++;
    };

    Value* get(Key key){
        for(int i = hashcode(key) % m_; keys_[i]; i = (i + 1) % m_){
            if (*(keys_[i]) == key){
                return values_[i];
            }
        }
        return nullptr;
    };

    bool contains(Key key){
        for(int i = hashcode(key) % m_; keys_[i]; i = (i + 1) % m_){
            if (*keys_[i] == key){
                return true;
            }
        }
        return false;
    };

    class Iterator;
private:
    int n_ = 0; // Number of key-value pairs
    int m_ = 16; // size of linear-probing table

    void resize(int newSize){
        std::vector<Key*> old_keys = keys_;
        std::vector<Value*> old_vals = values_;

        // Reset
        keys_.clear();
        values_.clear();
        keys_.resize(newSize);
        values_.resize(newSize);
        for (int i = 0; i < newSize; i++){
            keys_[i] = nullptr;
            values_[i] = nullptr;
        }

        // Rehash
        // TODO: this is a memory leak, the values in old_keys and
        // old_vals are never freed
        for (int i = 0; i < newSize; i++){
            if (old_keys[i]){
                put( *old_keys[i], *old_vals[i] );
            }
        }
    };
    
    Hash<Key> hashcode;
    std::vector<Key*> keys_;
    std::vector<Value*> values_;
};

template <class Key, class Value>
class HashMap<Key, Value>::Iterator {
public:
    Iterator(HashMap<Key, Value>* map) : map_(map), items_(map_.m_) {
        for (int i = 0; i < map->m_; i++){
            if (map->keys_[i]){
                items_.push_back({ map->keys_[i], map->values_[i] });
            }
        }
    }
    Iterator& operator++(){
        counter++;
        return *this;
    }
    Iterator operator++(int){
        Iterator old(*this);
        counter++;
        return old;
    }
    bool operator==(const Iterator& other){
        return other.map_ == map_ && other.counter == counter;
    }
    Pair<Key, Value&> operator*(){
        return Pair<Key, Value&>( *(items_[counter].first), items_[counter].second );
    }
private:
    HashMap<Key, Value>* map_;
    std::vector<Pair<Key*, Value*>> items_;
    size_t counter = 0;
};

// Hash implemented with separate chaining
// template <typename Key, typename Value>
// class HashMapSC {
//     public:
//         HashMapSC(){
//             m_ = 977;
//         };
// 
//         HashMapSC(int m){
//             m_ = m;
//         };
// 
//         void put(Key key, Value value){
// 
//         };
// 
//         Value get(Key key){
// 
//         };
// 
//         bool contains(Key key){
// 
//         }
//     private:
//         int n_ = 0;
//         int m_ = 997;
//         Hash<Key> hashcode;
// };


#endif // HASH_MAP_H_
