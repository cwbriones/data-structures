#include "Rope.h"
#include <cstdlib>
#include <iostream>

/**
 * Generates a random integer in
 * the range [a, b]
 */
int rand_int(int a, int b){
    int n = b - a + 1;

    int x;
    int max_limit = RAND_MAX - n;
    while ((x = rand()) >= max_limit){}
    return a + x % n;
}

/*
 * Rope public methods.
 */
Rope::Rope() : head_(nullptr), size_(0) {}
Rope::Rope(const std::string& str) : size_(str.size()) {
    std::cout << "Creating rope from string: " << str << std::endl;
    if (str.size() == 0) {
        head_ = nullptr;
    } else {
        head_ = std::make_shared<const Node>(str);
    }
}

Rope::Rope(const Rope& left, const Rope& right) : size_(left.size() + right.size()) {
    head_ = std::make_shared<const Node>(left.head_, right.head_, left.size());
}

size_t Rope::size() const {
    return size_;
}

std::string Rope::to_str() const {
    if (head_) {
        return head_->str();
    }
    return "";
}

char Rope::at(size_t pos) const {
    return head_->at(pos);
}

/*
 * Rope private methods.
 */

Rope::Node::Node() : left_(nullptr), right_(nullptr), data_(""), weight_(0) {}
Rope::Node::Node(
    std::shared_ptr<const Node> const & left, 
    std::shared_ptr<const Node> const & right, 
    size_t weight) :

    weight_(weight),
    data_(""),
    left_(left),
    right_(right) {}

Rope::Node::Node(const std::string& str) {
    if (str.size() > MIN_STR_LENGTH) {
        // Split the string somewhere in the middle
        int split_position = str.size()/2;
        // Assign recursively
        weight_ = split_position;
        left_ = std::shared_ptr<const Node>(new Node(str.substr(0, split_position)));
        right_ = std::shared_ptr<const Node>(new Node(str.substr(split_position)));
    } else {
        data_ = str;
        left_ = nullptr;
        right_ = nullptr;
        weight_ = str.size();
    }
}

std::string Rope::Node::str() const {
    if (!left_ && !right_) {
        return data_;
    }
    std::string left_str = left_->str();
    std::string right_str = right_->str();

    return left_str + right_str;
}

char Rope::Node::at(size_t pos) const {
    if (pos < weight_) {
        if (left_) {
            return left_->at(pos);
        } else {
            return data_[pos];
        }
    } else if (right_) {
        return right_->at(pos - weight_);
    }
}
