#ifndef HASH_SET_H
#define HASH_SET_H 

#include "Hash.h"

#include <iostream>
#include <vector>
#include <initializer_list>
// Hash implemented with linear probing
template <typename Key>
class HashSet {
public:
    HashSet() : keys_(m_, nullptr){}
    HashSet(int m) : keys_(m_, nullptr){}
    HashSet(std::initializer_list<Key> list) : HashSet(list.size() * 10) {
        for (auto& x : list){
            put(x);
        }
    }

    ~HashSet(){
        for (int i = 0; i < m_; i++){
            delete keys_[i];
        }
    }

    void put(Key key){
        if (n_ >= m_/2){
            resize(m_ * 2);
        }

        int i = hashcode(key) % m_;
        for(; keys_[i]; i = (i + 1) % m_){
            if (*(keys_[i]) == key){
                return;
            }
        }
        keys_[i] = new Key(key);
        n_++;
    };

    void remove(Key key){
        int i = hashcode(key) % m_;
        for(; keys_[i]; i = (i + 1) % m_){
            if (*(keys_[i]) == key){
                delete keys_[i];
                keys_[i] = nullptr;
            }
        }
        n_--;
    }

    bool contains(Key key){
        for(int i = hashcode(key) % m_; keys_[i]; i = (i + 1) % m_){
            if (*keys_[i] == key){
                return true;
            }
        }
        return false;
    };

    class Iterator;
    Iterator begin(){
        return Iterator(this);
    }
    Iterator end(){
        return Iterator(this, n_);
    }

    size_t size(){
        return n_;
    }

private:
    size_t n_ = 0; // Number of keys
    size_t m_ = 16; // size of linear-probing table

    void resize(int newSize){
        std::vector<Key*> old_keys = keys_;

        // Reset
        keys_.clear();
        keys_.resize(newSize);
        for (int i = 0; i < newSize; i++){
            keys_[i] = nullptr;
        }

        // Rehash
        for (int i = 0; i < newSize; i++){
            if (old_keys[i]){
                put( *old_keys[i] );
            }
        }
        for (auto& x : old_keys){
            delete x;
        }
    };
    
    Hash<Key> hashcode;
    std::vector<Key*> keys_;
};

template <class Key>
class HashSet<Key>::Iterator {
public:
    Iterator(HashSet<Key>* set, int counter) : counter(counter), set_(set), items_() {
        if (counter < set_->n_){
            items_.reserve(set->n_);
            for (int i = 0; i < set->m_; i++){
                if (set->keys_[i]){
                    items_.push_back(set->keys_[i]);
                }
            }
        }
    }
    Iterator(HashSet<Key>* set) : Iterator(set, 0) {};
    Iterator& operator++(){
        counter++;
        if (counter > items_.size()){
            counter = items_.size();
        }
        return *this;
    }
    Iterator operator++(int){
        Iterator old(*this);
        ++(*this);
        return old;
    }
    bool operator==(const Iterator& other){
        return other.set_ == set_ && other.counter == counter;
    }
    bool operator!=(const Iterator& other){
        return other.set_ != set_ || other.counter != counter;
    }
    Key& operator*(){
        return *items_[counter];
    }

private:
    HashSet<Key>* set_;
    std::vector<Key*> items_;
    size_t counter = 0;
};

#endif // HASH_SET_H
