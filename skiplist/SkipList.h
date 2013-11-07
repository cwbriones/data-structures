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
#include <iostream>

/**
 * Returns a number evenly distributed over the interval [0, 1]
 */
float frand(){
    return static_cast<float>(rand()) / RAND_MAX;
}

template <class Type>
class SkipList {
public:
    SkipList();
    ~SkipList();
    
    void insert(const Type& item);
    bool contains(const Type& item) const;
    int size();

    bool empty(){ return empty_; };

    Type* at(int index);

    class Iterator;
    Iterator begin();
    Iterator end();
private:
    int random_level();

    class Node;
    Node head_;

    int size_ = 0;
    bool empty_ = true;

    static const int MAX_LEVEL = 4;
    static constexpr float LEVEL_DIST = 0.5;
};

template <class Type>
class SkipList<Type>::Node {
public:
    Node(int height) : height(height){
        next = new Node * [height];
        width = new size_t [height];
        for (int i = 0; i < height; i++){
            next[i] = nullptr;
            width[i] = 0;
        }
    }
    Node(int height, const Type& data) : Node(height) {
        this->data = data;
    }
    ~Node(){
        delete[] next;
        delete[] width;
    }
private:
    Node** next;
    const int height;
    Type data;

    size_t* width;

    friend class SkipList<Type>;
};

/**
 * SkipList Constructor
 */
template <class Type>
SkipList<Type>::SkipList() : head_(MAX_LEVEL) {}

/**
 * SkipList Destructor
 */
template <class Type>
SkipList<Type>::~SkipList(){
    // Delete all nodes in the list
    
    Node* ptr = head_.next[0];
    
    while(ptr){
        Node* old = ptr;
        ptr = ptr->next[0];

        delete old;
    }
}

template <class Type>
inline int SkipList<Type>::size(){
    return size_;
}

/*
 * Returns the number of levels in a node over a geometric distribution
 * (i.e in the range [1, MAX_LEVEL]
 */
template <class Type>
int SkipList<Type>::random_level(){

    int lvl = 0;
    while ((++lvl != MAX_LEVEL) && frand() < LEVEL_DIST){}

    return lvl;
}

/**
 * Inserts the item into the SkipList.
 */
template <class Type>
void SkipList<Type>::insert(const Type& item){
    int index = 0;

    int levels = random_level();
    Node* new_node = new Node(levels, item); 

    Node* p = &head_;
    Node* prev[MAX_LEVEL];
    int prev_index[MAX_LEVEL];

    for (int i = MAX_LEVEL - 1; i >= 0; i--){
        // TODO:
        // Update the index of the nodes in previous as well
        // then since you know the old index + the index of the
        // newly inserted item you can update the widths of the
        // links
        while (p->next[i] && p->next[i]->data < item){
            index += p->width[i];
            p = p->next[i];
        }
        // Save all of the pointers in the prev lists
        prev[i] = p;
        prev_index[i] = index;
    }

    // Connect it into each list with the same level
    for (int i = 0; i < levels; i++){
        Node* after = prev[i]->next[i];
        prev[i]->next[i] = new_node;
        new_node->next[i] = after;
        
        // Update link widths
        int old_width = prev[i]->width[i];
        // "Cut"
        prev[i]->width[i] = index - prev_index[i] + 1;
        // Give "excess" to new node
        new_node->width[i] = old_width - prev[i]->width[i];
    }

    ++size_;
    empty_ = false;
}

#include <stdexcept>

template <class Type>
Type* SkipList<Type>::at(int index){

    if (index >= size_ || index < 0){
        throw std::out_of_range("Index out of range [0, size) for skiplist ");
    }
    Node* p = &head_;

    int p_index = 0;
    for (int i = MAX_LEVEL - 1; i >= 0; i--){
        // Equivalent to 
        // while ( we don't overshoot )
        // just like with item search
        while (p_index + p->width[i] <= index){
            p_index += p->width[i];
            p = p->next[i];
        }
    }
    if (p->next[0]){
        return &p->next[0]->data;
    }
    return nullptr;
}

/**
 * Returns true if the item is contained in the SkipList.
 */
template <class Type>
bool SkipList<Type>::contains(const Type& item) const {
    if (empty_){
        return false;
    }

    const Node* p = &head_;

    for (int i = MAX_LEVEL; i >= 0; i--){
        while (p->next[i] && p->next[i]->data <= item){
           p = p->next[i]; 
        }
    }
    return (p && p->data == item);
}

template <class Type>
typename SkipList<Type>::Iterator SkipList<Type>::begin(){
    return Iterator(*this);
}

template <class Type>
typename SkipList<Type>::Iterator SkipList<Type>::end(){
    return Iterator(*this, nullptr);
}

/**
 * Iterator class for traversing the SkipList
 */
template <class Type>
class SkipList<Type>::Iterator {
public:
    Iterator(const SkipList<Type>& list){
        iter_ = list.head_.next[0];
    }

    Iterator(const SkipList<Type>& list, Node* start){
        iter_ = start;
        if (iter_ == &list.head_){
            iter_ = list.head_.next[0];
        }
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
