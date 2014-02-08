#include "Rope.h"

Rope::Rope() : head_(nullptr) {}
Rope::Rope(const std::string& str) : head_(new Rope::Node(str)) {}
Rope::~Rope() {
    delete head_;
}

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
