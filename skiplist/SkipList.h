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

#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <cstdlib>
#include <cmath>

/**
 * Returns a number evenly distributed over the interval [0, 1)
 */
float frand(){
    return (float) rand() / RAND_MAX;
}

template <class Type>
class SkipList {
public:
    SkipList();
    ~SkipList();
    
    void insert(const Type& item);
    bool contains(const Type& item) const;

    class Iterator;
    Iterator begin();
    Iterator end();
private:
    int random_level();

    class Node;
    Node* head_ = nullptr;
    int size_ = 0;

    static const int MAX_LEVEL = 6;
    static constexpr float LEVEL_DIST = 0.5;
};

template <class Type>
class SkipList<Type>::Node {
public:
    Node(int height, Type data) : height(height), data(data) {
        next = new Node * [height];
        for (int i = 0; i < height; i++){
            next[i] = nullptr;
        }
    }

    ~Node(){
        delete next;
    }
private:
    Node** next;
    const int height;
    Type data;
};

/*
 * Returns the number of levels in a node over a geometric distribution
 */
template <class Type>
int SkipList<Type>::random_level(){
    int lvl = static_cast<int>(log( frand() / (1.0 - LEVEL_DIST)));
    return lvl > MAX_LEVEL ? MAX_LEVEL : lvl;
}

/**
 * SkipList Constructor
 */
template <class Type>
SkipList<Type>::SkipList(){
}

/**
 * SkipList Destructor
 */
template <class Type>
SkipList<Type>::~SkipList(){
    delete head_;
}

/**
 * Inserts the item into the SkipList.
 */
template <class Type>
void SkipList<Type>::insert(const Type& item){
    if (!head_){
        head_ = new Node(MAX_LEVEL, item);
        return;
    }

    Node* p = head_;
    for (int i = MAX_LEVEL; i >= 0; i--){
        while (p->next[i] && p->next[i]->value < item){
            p = p->next[i];
        }
    }
    // P now points to a spot for our element
    p->next[0] = new Node( random_level(), item);
    // Connect it into each list with the same level
    size_++;
}

/**
 * Returns true if the item is contained in the SkipList.
 */
template <class Type>
bool SkipList<Type>::contains(const Type& item) const {
    if (!size_){
        return false;
    }

    Node* p = head_;
    for (int i = MAX_LEVEL; i >= 0; i--){
        while (p->next[i] && p->next[i]->value < item){
           p = p->next[i]; 
        }
    }
    p = p->next[0];
    return (p && p->value == item);
}

/**
 * Iterator class for traversing the SkipList
 */
template <class Type>
class SkipList<Type>::Iterator {
public:
    Iterator(const SkipList<Type>& list){
        iter_ = list.head;
    }
    Iterator operator++(){
        if (iter_){
            iter_ = iter_->next[0];
        }
        return (*this);
    }
    Iterator operator++(int){
        Iterator old(*this);
        ++(*this);
        return old;
    }
    const Type& operator*(){
        return iter_->data;
    }
    bool operator==(const Iterator& other){
        return other.iter_ == iter_;
    }
    bool operator!=(const Iterator& other){
        return other.iter_ != iter_;
    }
private:
    Node* iter_;
};

#endif // SKIP_LIST_H_
