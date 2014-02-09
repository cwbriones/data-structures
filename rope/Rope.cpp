#include "Rope.h"
#include <cstdlib>

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

Rope::Rope() : head_(nullptr) {}
Rope::Rope(const std::string& str) : head_(new Rope::Node(str)) {}
Rope::~Rope() {
    delete head_;
}

const size_t Rope::size() const {
    if (head_) {
        return head_->weight();
    }
    return 0;
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

Rope::Node::Node() : left_(nullptr), right_(nullptr), data_("") {
    weight_ = 0;
}

Rope::Node::Node(const std::string& str) : left_(nullptr), right_(nullptr) {
    if (str.size() > MIN_STR_LENGTH) {
        // Split the string somewhere in the middle
        int split_position = rand_int(0.25 * str.size(), 0.75 * str.size());
        // Assign recursively
        left_ = new Node(str.substr(0, split_position));
        right_ = new Node(str.substr(split_position));
        update_weight();
    } else {
        data_ = str;
        weight_ = str.size();
    }
}

Rope::Node::~Node() {
    delete left_;
    delete right_;
}

size_t Rope::Node::update_weight() { 
    if (!left_) {
        weight_ = data_.size();
    } else {
        weight_ = left_->update_weight();
    }

    if (right_) {
        return weight_ + right_->update_weight();
    } else {
        return weight_;
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
