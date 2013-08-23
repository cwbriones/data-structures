#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <vector>
#include <string>
#include <functional>

#include "Hash.h"

// Useful struct for iteration, mirrors std::pair
template <class Key, class Value>
struct Pair {
    Pair(const Key& key, const Value& value) :
        first(key), second(value) {}
    Key first;
    Value second;
};

// Simplifies object creation with the use of auto
template <class Key, class Value>
Pair<Key, Value> create_pair(const Key& key, const Value& value){
    return Pair<Key, Value>(key, value);
}

// Hash Table implemented with linear probing
template <typename Key, typename Value>
class HashMap {
public:
    HashMap();
    ~HashMap();

    void put(const Key& key, const Value& value);
    Value* get(const Key& key);
    void remove(const Key& key);

    bool contains(const Key& key) const;

    float max_load() const {
        return maxLoad_;
    }
    void set_max_load(float maxLoad){
        maxLoad_ = maxLoad;
    }

    class Iterator;
private:
    int size_ = 0; // Number of key-value pairs
    int tableSize_ = 41; // size of linear-probing table

    float maxLoad_ = 0.25;
    void resize(int newSize);
    
    Hash<Key> hashcode;
    std::vector< Pair<Key, Value>* > items_;
};

template <class Key, class Value>
HashMap<Key, Value>::HashMap() : items_(tableSize_, nullptr) {}

template <class Key, class Value>
HashMap<Key, Value>::~HashMap(){
    for (int i = 0; i < tableSize_; i++){
        if (items_[i]){
            delete items_[i];
        }
    }
}

template <class Key, class Value>
void HashMap<Key, Value>::put(const Key& key, const Value& value){
    // Double the size of the linear-probing table if
    // the load factor exceeds the max
    if (size_ >= static_cast<int>(tableSize_ * maxLoad_)){
        resize(tableSize_ * 2);
    }

    // Compute starting point of probe
    int i = hashcode(key) % tableSize_;
    // Probe for empty slot
    for(; items_[i]; i = (i + 1) % tableSize_){
        if (items_[i]->first == key){
            items_[i]->second = value;
            return;
        }
    }
    // Otherwise empty slot
    items_[i] = new Pair<Key, Value>(key, value);
    size_++;
}

template <class Key, class Value>
Value* HashMap<Key, Value>::get(const Key& key){
    for(int i = hashcode(key) % tableSize_; items_[i]; i = (i + 1) % tableSize_){
        if (items_[i]->first == key){
            return &items_[i]->second;
        }
    }
    return nullptr;
}

template <class Key, class Value>
bool HashMap<Key, Value>::contains(const Key& key) const {
    for(int i = hashcode(key) % tableSize_; items_[i]; i = (i + 1) % tableSize_){
        if (items_[i]->first == key){
            return true;
        }
    }
    return false;
}

template <class Key, class Value>
void HashMap<Key, Value>::resize(int newSize){
    // std::vector<Key*> old_keys = keys_;
    // std::vector<Value*> old_vals = values_;

    // // Reset
    // keys_.clear();
    // values_.clear();
    // keys_.resize(newSize);
    // values_.resize(newSize);
    // for (int i = 0; i < newSize; i++){
    //     keys_[i] = nullptr;
    //     values_[i] = nullptr;
    // }

    // // Rehash
    // // TODO: this is a memory leak, the values in old_keys and
    // // old_vals are never freed
    // for (int i = 0; i < newSize; i++){
    //     if (old_keys[i]){
    //         put( *old_keys[i], *old_vals[i] );
    //     }
    // }
};

template <class Key, class Value>
class HashMap<Key, Value>::Iterator {
public:
    Iterator(HashMap<Key, Value>* map) : map_(map), items_(map_.tableSize_) {
        for (int i = 0; i < map->tableSize_; i++){
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

#endif // HASH_MAP_H_
