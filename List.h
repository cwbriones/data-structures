#ifndef MY_LIST_H
#define MY_LIST_H

#include <cstdlib>

template <class T>
struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    T data;
};

template <class T>
class List {
public:
    List(){};
    ~List(){};

    void append(T item);
    void prepend(T item);

    const Node<T>* head(){ return head_; };
private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t size_ = 0;
};

template <class T>
void List<T>::prepend(T item){
    Node<T>* new_ = new Node<T>();
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

template <class T>
void List<T>::append(T item){
    Node<T>* new_ = new Node<T>();
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

#endif //MY_LIST_H
