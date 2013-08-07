#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib>
#include <cassert>
#include <iostream>

template <class T>
class Array
{
public:
    Array();
    ~Array();

    void push_back(T item);
    T get(size_t i) const;
    void set(size_t i, T item);

    void expand();
    void reserve(size_t new_size_);
    size_t size() const;

    T& operator[](size_t i);
private:
    void resize(size_t new_size_);

    int expand_rate_ = 2;
    T* data_ = nullptr;

    size_t size_ = expand_rate_;
    size_t end_ = 0;
};

template <class T>
T& Array<T>::operator[](size_t i){
    assert(i < size_);
    return (data_[i]);
}

template <class T>
Array<T>::Array(){
    data_ = new T[expand_rate_]; 
};

template <class T>
Array<T>::~Array(){
    delete[] data_;
};

template <class T>
void Array<T>::push_back(T item){
    if (end_ >= size_){
        expand();
    }
    data_[end_] = item;
    end_++;
};

template <class T>
T Array<T>::get(size_t i) const {
    assert(i < size_);
    return data_[i];
};

template <class T>
void Array<T>::set(size_t i, T item){
    assert(i < size_);

    int new_size_ = size_;
    while (i > new_size_){
        new_size_ *= expand_rate_;
    }
    if (new_size_ > size_){
        resize(new_size_);
    }
    if (i > end_){
        end_ = i;
    }
    data_[i] = item;
};

template <class T>
void Array<T>::reserve(size_t new_size_){
    if (new_size_ > size_){
        resize(new_size_);
    }
};

template <class T>
size_t Array<T>::size() const { return end_; };

template <class T>
void Array<T>::expand(){
    resize(size_ * expand_rate_);
};

template <class T>
void Array<T>::resize(size_t new_size_){
    std::cout << "Resizing array (" << this << ") from " << size_ << " to " << new_size_
        << "." << std::endl;
    assert(new_size_ > size_);
    T* new_data_ = new T[new_size_];

    for (int i = 0; i < end_; i++){
        new_data_[i] = data_[i];
    }
    delete[] data_;

    data_ = new_data_;
    size_ = new_size_;
};

#endif
