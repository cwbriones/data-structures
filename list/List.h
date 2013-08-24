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

#ifndef MY_LIST_H
#define MY_LIST_H

#include <cstdlib>

/**
 * A generic doubly-linked List container class.
 */
template <class T>
class List {
public:
    List();
    ~List();

    void append(const T& item);
    void prepend(const T& item);
    void reverse();

    class Iterator;
    Iterator begin();
    Iterator end();
private:
    struct Node {
        Node* next = nullptr;
        Node* prev = nullptr;
        T data;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
};

template <class T>
List<T>::List(){}

template <class T>
List<T>::~List(){
    auto iter = head_;
    while (iter){
        auto old = iter;
        iter = iter->next;

        delete old;
    }
}

template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

/**
 * Adds an item onto the head of the List.
 */
template <class T>
void List<T>::prepend(const T& item){
    Node* new_ = new Node();
    new_->data = item;

    if (size_ > 0){
        head_->prev = new_;
        new_->next = head_;
        head_ = new_;
    } else {
        head_ = new_;
        tail_ = new_;
    }
    size_++;
}

/**
 * Adds an item onto the tail of the List.
 */
template <class T>
void List<T>::append(const T& item){
    Node* new_ = new Node();
    new_->data = item;

    if(size_ > 0){
        tail_->next = new_;
        new_->prev = tail_;
        tail_ = new_;
    }
    else {
        head_ = new_;
        tail_ = new_;
    }
    size_++;
}
/**
 * Reverses the order of the elements in the List.
 *
 * This does not change the direction of iterators, so reversing a list
 * while iterating over it can result in unexpected results.
 */
template <class T>
void List<T>::reverse(){
    Node* node = head_;
    while (node){
        swap(node->next, node->prev);
        node = node->prev;
    }
    swap(head_, tail_);
}

/**
 * Returns an Iterator pointing to the head of the list.
 */
template <class T>
typename List<T>::Iterator List<T>::begin(){ 
    return Iterator(this, head_);
}

/**
 * Returns an Iterator pointing to the element past-the-end of the list.
 */
template <class T>
typename List<T>::Iterator List<T>::end(){ 
    return Iterator(this, nullptr);
}

/**
 * A bi-directional iterator to the elements in a Linked-List container.
 */
template <class T>
class List<T>::Iterator {
public:
    Iterator(List* list, Node* iter) : list_(list), iter_(iter) {}
    Iterator operator++(){ 
        if (iter_){
            iter_ = iter_->next;
        }
        return *this;
    }
    Iterator operator++(int){
        Iterator old(*this);
        ++(*this);
        return old;
    }
    Iterator operator--(){
        if (iter_ && iter_->prev){
            iter_ = iter_->prev;
        }
        return (*this);
    }
    Iterator operator--(int){
        Iterator old(*this);
        --(*this);
        return old;
    }
    bool operator==(const Iterator& rhs){
        return (list_ == rhs.list_) && (iter_ == rhs.iter_);
    }
    bool operator!=(const Iterator& rhs){
        return (list_ != rhs.list_) || (iter_ != rhs.iter_);
    }
    T& operator*(){ 
        return iter_->data;
    }
private:
    List* list_;
    Node* iter_ = nullptr;
};

#endif //MY_LIST_H
