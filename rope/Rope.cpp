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

/*
 * Rope private methods.
 */

Rope::Node::Node() : left_(nullptr), right_(nullptr), data_("") {
    weight_ = 0;
}

Rope::Node::Node(const std::string& str) : left_(nullptr), right_(nullptr), data_(str) {
    weight_ = str.size();
}

Rope::Node::~Node() {
    delete left_;
    delete right_;
}

std::string Rope::Node::str() const {
    return data_;
}
