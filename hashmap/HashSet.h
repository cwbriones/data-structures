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

#ifndef HASH_SET_H_
#define HASH_SET_H

#include <vector>
#include <string>
#include <functional>

#include <initializer_list>

#include "Hash.h"

/**
 * HashSet container class implemented with linear probing
 */
template <class Key>
class HashSet {
public:
    HashSet();
    HashSet(std::initializer_list<const Key> list);
    ~HashSet();

    void put(const Key& key);
    void remove(const Key& key);
    bool contains(const Key& key) const;

    float max_load() const {
        return maxLoad_;
    }
    void set_max_load(float maxLoad){
        maxLoad_ = maxLoad;
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
    std::vector<Key* > items_;
};

template <class Key>
HashSet<Key>::HashSet() : items_(tableSize_, nullptr) {}

template <class Key>
HashSet<Key>::HashSet(std::initializer_list<const Key> list) : HashSet() {
    for (auto& x : list){
        put(x);
    }
}

template <class Key>
HashSet<Key>::~HashSet(){
    for (int i = 0; i < tableSize_; i++){
        if (items_[i]){
            delete items_[i];
        }
    }
}

/**
 * Inserts the key-value pair into the HashSet.
 */
template <class Key>
void HashSet<Key>::put(const Key& key){
    // Double the size of the linear-probing table if
    // the load factor exceeds the max
    if (size_ >= static_cast<int>(tableSize_ * maxLoad_)){
        resize(tableSize_ * 2);
    }

    // Compute starting point of probe
    int i = hashcode(key) % tableSize_;
    // Probe for empty slot
    for(; items_[i]; i = (i + 1) % tableSize_){
        if (*items_[i] == key){
            return;
        }
    }
    // Otherwise empty slot
    items_[i] = new Key(key);
    size_++;
}

/**
 * Returns true if the key is contained in the HashSet.
 */
template <class Key>
bool HashSet<Key>::contains(const Key& key) const {
    for(int i = hashcode(key) % tableSize_; items_[i]; i = (i + 1) % tableSize_){
        if (*items_[i] == key){
            return true;
        }
    }
    return false;
}

/*
 * Removes a key-value pair from the HashSet. May possibly trigger a rehash.
 */
template <class Key>
void HashSet<Key>::remove(const Key& key) {
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
        put(*redoItem[i]->first);
        i = (i + 1) % tableSize_;
        delete redoItem;
    }
    size_--;
    // Possibly add a trigger to a rehash to a smaller table
    return;
}

template <class Key>
inline size_t HashSet<Key>::size() const {
    return size_;
}

/** 
 * Resizes the HashSet and rehashes all of the key-value pairs into new
 * locations.
 */
template <class Key>
void HashSet<Key>::resize(int newSize){
    std::vector<Key*> old = items_;

    // Reset
    items_.resize(newSize);
    for (int i = 0; i < newSize; i++){
        items_[i] = nullptr;
    }

    // Rehash
    for (int i = 0; i < tableSize_; i++){
        if (old[i]){
            int i = hashcode(*old[i]) % tableSize_;
            while(items_[i]){
                i = (i + 1) % tableSize_;
            }
            items_[i] = old[i];
        }
    }
    tableSize_ = newSize;
};

template <class Key>
typename HashSet<Key>::Iterator HashSet<Key>::begin() const {
    return Iterator(this, 0);
}

template <class Key>
typename HashSet<Key>::Iterator HashSet<Key>::end() const {
    Iterator iter(this, tableSize_);

    return iter;
}

/**
 * An iterator class for accessing the elements
 * of the HashSet in no particular order.
 *
 * It is the responsibility of the client to no longer use an iterator
 * after the map has been altered or destroyed.
 *
 * Dereferencing an iterator that points to the end of the container
 * results in undefined behaivour.
 */
template <class Key>
class HashSet<Key>::Iterator {
public:
    Iterator(const HashSet<Key>* set, int counter) : set_(set), counter_(counter) {
        if (set_->size_ > 0){
            // Find the first non-null element in the table
            while (!set_->items_[counter_]){
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
        return other.set_ == set_ && other.counter_ == counter_;
    }
    bool operator!=(const Iterator& other){
        return other.set_ != set_ || other.counter_ != counter_;
    }
    const Key& operator*(){
        return *(set_->items_[counter_]);
    }
private:
    const HashSet<Key>* set_;
    size_t counter_ = 0;

    /** 
     * Guarantees the counter moves at least once,
     * then continues until we have a non-null element
     * or reach the end.
     */
    void increment(){
        counter_++;
        while (counter_ < set_->tableSize_ && !set_->items_[counter_]){
            counter_++;
        }
        if (counter_ > set_->tableSize_){
            counter_ = set_->tableSize_;
        }
    }
};
#endif // HASH_SET_H_
