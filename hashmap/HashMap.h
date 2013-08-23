#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <vector>
#include <string>
#include <functional>

#include "Hash.h"

// Useful struct for iteration, mirrors std::pair
template <class Key, class Value>
struct Pair {
    Key first;
    Value second;
};

// Simplifies object creation with the use of auto
template <class Key, class Value>
Pair<Key, Value> create_pair(const Key& key, const Value& value){
    return Pair<Key, Value>(key, value);
}

/**
 * Hash Table container class implemented with linear probing
 */
template <typename Key, typename Value>
class HashMap {
public:
    HashMap();
    ~HashMap();

    void put(const Key& key, const Value& value);
    Value& get(const Key& key);
    void remove(const Key& key);

    bool contains(const Key& key) const;

    float max_load() const {
        return maxLoad_;
    }
    void set_max_load(float maxLoad){
        maxLoad_ = maxLoad;
    }
    Value& operator[](const Key& key){
        return get(key);
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

/**
 * Inserts the key-value pair into the HashMap.
 */
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
    items_[i] = new Pair<Key, Value>();
    items_[i]->first = key;
    items_[i]->second = value;
    size_++;
}

/** 
 * Returns a reference to the value in the HashMap at key.
 * Creates a new pair if not in the map.
 */
template <class Key, class Value>
Value& HashMap<Key, Value>::get(const Key& key){
    int i = hashcode(key) % tableSize_;
    for(; items_[i]; i = (i + 1) % tableSize_){
        if (items_[i]->first == key){
            return items_[i]->second;
        }
    }
    // Create a new key-value pair and return reference
    // to the value.
    items_[i] = new Pair<Key, Value>();
    items_[i]->first = key;

    return items_[i]->second;
}

/**
 * Returns true if the key is contained in the HashMap.
 */
template <class Key, class Value>
bool HashMap<Key, Value>::contains(const Key& key) const {
    for(int i = hashcode(key) % tableSize_; items_[i]; i = (i + 1) % tableSize_){
        if (items_[i]->first == key){
            return true;
        }
    }
    return false;
}

/** 
 * Resizes the HashMap and rehashes all of the key-value pairs into new
 * locations.
 */
template <class Key, class Value>
void HashMap<Key, Value>::resize(int newSize){
    std::vector<Pair<Key, Value>*> old = items_;

    // Reset
    items_.clear();
    items_.resize(newSize);
    for (int i = 0; i < newSize; i++){
        items_[i] = nullptr;
    }

    // Rehash
    for (int i = 0; i < tableSize_; i++){
        if (old[i]){
            int i = hashcode(old[i]->first) % tableSize_;
            while(items_[i]){
                i = (i + 1) % tableSize_;
            }
            items_[i] = old[i];
        }
    }

    tableSize_ = newSize;
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
