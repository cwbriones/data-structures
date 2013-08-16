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

    void reverse();
    void append(T item);
    void prepend(T item);

    const Node<T>* head(){ return head_; };

    class Iterator {
    public:
        Iterator(List* list, Node<T>* iter) : list_(list), iter_(iter) {}
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
        // Iterator& operator--(){
        //     if (iter_->prev){
        //         iter_ = iter_->prev;
        //     }
        //     return *this;
        // }
        bool operator==(const Iterator& rhs){
            return (list_ == rhs.list_) && (iter_ == rhs.iter_);
        }
        bool operator!=(const Iterator& rhs){
            return (list_ != rhs.list_) || (iter_ != rhs.iter_);
        }
        T& operator*(){ return iter_->data; }
    private:
        List* list_;
        Node<T>* iter_ = nullptr;
    };
    Iterator begin(){ return Iterator(this, head_); }
    Iterator end(){ return Iterator(this, nullptr); }
private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_t size_ = 0;
};

template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

template <class T>
void List<T>::reverse(){
    Node<T>* node = head_;
    while (node){
        swap(node->next, node->prev);
        node = node->prev;
    }
    swap(head_, tail_);
}

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
