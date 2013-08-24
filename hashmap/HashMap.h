/*
 * Copyright (C) 2013 Christian Briones
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <vector>
#include <iostream>
#include <string>
#include <functional>

#include "Hash.h"

// Useful struct for iteration, mirrors std::pair
template <class Key, class Value>
struct Pair {
    Pair(){}
    Pair(Key key, Value value) : first(key), second(value) {}
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
    size_t size() const;

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
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
    size_++;

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

/*
 * Removes a key-value pair from the HashMap. May possibly trigger a rehash.
 */
template <class Key, class Value>
void HashMap<Key, Value>::remove(const Key& key) {
    // Search for item and delete it.
    if (!contains(key)){
        return;
    }
    int i = hashcode(key);
    while (items_[i]->first != key){
        i = (i + 1) % tableSize_;
    }
    // Removal
    delete items_[i];
    items_[i] = nullptr;
    // Rehashing
    while (items_[i]){
        auto redoItem = items_[i];
        items_[i] = nullptr;
        size_--;
        put(redoItem[i]->first, redoItem[i]->second);
        i = (i + 1) % tableSize_;
        delete redoItem;
    }
    size_--;
    // Possibly add a trigger to a rehash to a smaller table
    return;
}

template <class Key, class Value>
inline size_t HashMap<Key, Value>::size() const {
    return size_;
}

/** 
 * Resizes the HashMap and rehashes all of the key-value pairs into new
 * locations.
 */
template <class Key, class Value>
void HashMap<Key, Value>::resize(int newSize){
    std::vector<Pair<Key, Value>*> old = items_;

    // Reset
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
typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::begin() const {
    return Iterator(this, 0);
}

template <class Key, class Value>
typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::end() const {
    Iterator iter(this, tableSize_);

    return iter;
}

/**
 * An iterator class for accessing the elements
 * of the HashMap in no particular order.
 *
 * It is the responsibility of the client to no longer use an iterator
 * after the map has been altered or destroyed.
 *
 * Dereferencing an iterator that points to the end of the container
 * results in undefined behaivour.
 */
template <class Key, class Value>
class HashMap<Key, Value>::Iterator {
public:
    Iterator(const HashMap<Key, Value>* map, int counter) : map_(map), counter_(counter) {
        if (map_->size_ > 0){
            // Find the first non-null element in the table
            while (!map_->items_[counter_]){
                counter_++;
            }
        }
    }

    Iterator& operator++(){
        increment();
        return *this;
    }
    Iterator operator++(int){
        Iterator old(*this);
        increment();
        return old;
    }
    bool operator==(const Iterator& other){
        return other.map_ == map_ && other.counter_ == counter_;
    }
    bool operator!=(const Iterator& other){
        return other.map_ != map_ || other.counter_ != counter_;
    }
    Pair<const Key&, Value&> operator*(){
        auto iter = map_->items_[counter_];
        return Pair<const Key&, Value&>(iter->first, iter->second);
    }
private:
    const HashMap<Key, Value>* map_;
    size_t counter_ = 0;

    /** 
     * Guarantees the counter moves at least once,
     * then continues until we have a non-null element
     * or reach the end.
     */
    void increment(){
        counter_++;
        while (counter_ < map_->tableSize_ && !map_->items_[counter_]){
            counter_++;
        }
        if (counter_ > map_->tableSize_){
            counter_ = map_->tableSize_;
        }
    }
};

#endif // HASH_MAP_H_
