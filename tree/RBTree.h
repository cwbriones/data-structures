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

#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>
#include <initializer_list>
#include <list>

static const bool BLACK = false;
static const bool RED = true;

template <class Key, class Value>
struct Pair {
    Pair(Key first, Value second){
        this->first = first;
        this->second = second;
    }
    Key first;
    Value second;
};

template <class Key, class Value>
Pair<Key, Value> make_pair(Key first, Value second){
    return Pair<Key, Value>(first, second);
}

/**
 * Implements a symbol table using a Red-Black tree.
 */
template <class Key, class Value>
class RBTree {
public:
    RBTree();
    RBTree(std::initializer_list<Pair<Key,Value> > list);
    ~RBTree();
    class Iterator;

    void put(const Key& key, const Value& val);
    Iterator get(const Key& key);
    bool contains(const Key& key) const;

    void clear();

    Iterator floor(const Key& key);
    Iterator ceiling(const Key& key);

    Iterator min();
    Iterator max();

    Iterator begin();
    Iterator end();
private:
    struct Node;

    Node* root_ = nullptr;
    Node* put(Node* root, const Key& key, const Value& val);
    Value* get(Node* root, const Key& key);

    int size(Node* node);
    bool is_red(Node* node);

    Node* min(Node* root);
    Node* max(Node* root);

    void clear_tree(Node* root);
    void flip_colors(Node* node);
    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
};

template <class Key, class Value>
struct RBTree<Key, Value>::Node {
    Node(Key key, Value val, int size, bool color) :
        key(key), val(val), size(size), color(color) {}
    Key key;
    Value val;
    Node* left = nullptr;
    Node* right = nullptr;

    int size = 0;
    bool color = BLACK;
};

template <class Key, class Value>
RBTree<Key, Value>::RBTree(){}

template <class Key, class Value>
RBTree<Key, Value>::RBTree(std::initializer_list<Pair<Key,Value> > list){
    for (auto& x : list){
        put(x.first, x.second);
    }
}

template <class Key, class Value>
RBTree<Key, Value>::~RBTree(){
    clear();
}

template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::floor(const Key& key){
    Node* item = get(root_, key);
    if (item){
        return Iterator(*this, max(item->left));
    }
    return end();
}

template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::ceiling(const Key& key){
    Node* item = get(root_, key);
    if (item){
        return Iterator(*this, min(item->right));
    }
    return end();
}

template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::min(){
    return Iterator(*this);
}

template <class Key, class Value>
typename RBTree<Key,Value>::Iterator RBTree<Key, Value>::max(){
    auto max_n = max(root_);

    return Iterator(*this, max_n);
}

template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::min(Node* root){
    if (root->left){
        return min(root->left);
    } else {
        return root;
    }
}

template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::max(Node* root){
    while (root->right){
        root = root->right;
    }
    return root;
}

/**
 * Destroys all the nodes in the tree.
 */
template <class Key, class Value>
void RBTree<Key, Value>::clear(){
    clear_tree(root_);
    root_ = nullptr;
}

/**
 * Destroys the subtree at the given root.
 */
template <class Key, class Value>
void RBTree<Key, Value>::clear_tree(Node* root){
    if (!root){
        return;
    } else {
        clear_tree(root->left);
        clear_tree(root->right);
    }
    delete root;

    return;
}

template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::begin(){
    return Iterator(*this);
}

template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::end(){
    return Iterator(*this, nullptr);
}

/**
 * Recursively searches for the value at the key in the tree.
 * Returns an iterator to the node.
 *
 * TODO: This behaivior shuold correspond to RBTree::find(Key& key) while
 * RBTree::get(Key& key) should behave like in the HashMap and create a node
 * if it already isn't in the tree, returning a reference.
 */
template <class Key, class Value>
typename RBTree<Key, Value>::Iterator RBTree<Key, Value>::get(const Key& key){
    return Iterator(*this, key);
}

/**
 * Recursively searches for the value at key in the subtree with the given root.
 * Returns a pointer to the value if it is found, otherwise nullptr.
 */
template <class Key, class Value>
Value* RBTree<Key, Value>::get(Node* root, const Key& key){
    if (!root){
        return nullptr;
    }
    
    if (key < root->key){
        return get(root->left, key);
    }
    else if (key > root->key){
        return get(root->right, key);
    }
    else {
        return (root->key == key) ? &root->val : nullptr;
    }
}

/**
 * Recursively inserts the key-value pair into the tree and updates the root.
 */
template <class Key, class Value>
void RBTree<Key, Value>::put(const Key& key, const Value& val){
    root_ = put(root_, key, val);
    root_->color = BLACK;
}

/**
 * Returns true if key is contained within the tree.
 */
template <class Key, class Value>
bool RBTree<Key, Value>::contains(const Key& key) const {
    // Search for the key
    Node* p = root_;
    while (p){
        if (p->key > key){
            p = p->left;
        } 
        else if (p->key < key){
            p = p->right;
        }
        else {
            return (p->key == key);
        }
    }
    return false;
}

/**
 * Returns the size of the subtree rooted at the given node.
 */
template <class Key, class Value>
int RBTree<Key, Value>::size(Node* node){
    if (!node){
        return 0;
    }
    return node->size;
}

template <class Key, class Value>
bool RBTree<Key, Value>::is_red(Node* node){
    return (node && node->color == RED);
}

/**
 * Changes the color of the node.
 */
template <class Key, class Value>
void RBTree<Key, Value>::flip_colors(Node* node){
    node->left->color = BLACK;
    node->right->color = BLACK;

    node->color = RED;
}

/**
 * "Rotates" a node counter-clockwise with respect to its parent and sibling.
 */
template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::rotate_left(Node* node){
    Node* other = node->right;
    node->right = other->left;
    other->left = node;

    other->color = node->color;
    node->color = RED;

    other->size = node->size;
    node->size = 1 + size(node->left) + size(node->right);

    return other;
}

/**
 * "Rotates" a node clockwise with respect to its children.
 */
template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::rotate_right(Node* node){
    Node* other = node->left;
    node->left = other->right;
    other->right = node;

    other->color = node->color;
    node->color = RED;

    other->size = node->size;
    node->size = 1 + size(node->left) + size(node->right);

    return other;
}

/**
 * Recursively inserts a key-value pair into the subtree at the given root,
 * and then balances the tree.
 */
template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::
    put(Node* root, const Key& key, const Value& val){
    if (!root){
        return new Node(key, val, 1, RED);
    }
    // Insert the node as usual
    if (key < root->key){
        root->left = put(root->left, key, val);
    }
    else if (key > root->key){
        root->right = put(root->right, key, val);
    }
    else {
        root->val = val;
    }

    // Balance the tree
    if (is_red(root->right) && !is_red(root->left)){
        root = rotate_left(root);
    }
    if (is_red(root->left) && is_red(root->left->left)){
        root = rotate_right(root);
    }
    if (is_red(root->left) && is_red(root->right)){
        flip_colors(root);
    }
    // Update size
    root->size = 1 + size(root->left) + size(root->right);

    return root;
}

/**
 * An Iterator class for accessing the elements
 * of the RBTree in increasing order.
 *
 * It is the responsibility of the client to no longer use
 * an iterator after the Tree has been destroyed.
 *
 * Dereferencing an iterator that points to the end of the
 * container results in undefined behaivour.
 */
template <class Key, class Value>
class RBTree<Key, Value>::Iterator {
public:
    Iterator(RBTree<Key, Value>& tree) : tree_(tree) {
        iter_ = tree.root_;
        while (iter_){
            if (iter_->left){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            } else {
                break;
            }
        }
    }
    Iterator(RBTree<Key, Value>& tree, Node* iter) : tree_(tree) {
        if (!iter){
            return;
        }
        iter_ = tree.root_;
        while (iter_ != iter){
            if (iter_->key > iter->key){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            }
            else if (iter_->key < iter->key){
                iter_ = iter_->right;
            }
        }
    }

    Iterator(RBTree<Key, Value>& tree, const Key& key) : tree_(tree) {
        iter_ = tree.root_;
        while (iter_ && iter_->key != key){
            if (iter_->key > key){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            }
            else if (iter_->key < key){
                iter_ = iter_->right;
            }
        }
    }

    Iterator operator++(){
        while (!visit_stack.empty() || iter_){
            if (iter_ && !check_right){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            }
            else {
                // Parent stack guaranteed nonempty
                if (!check_right){
                    check_right = true;
                    iter_ = visit_stack.back();
                    visit_stack.pop_back();
                    break; // Return with iterator at this element.
                } else {
                    // return the node and then continue
                    check_right = false;
                    iter_ = iter_->right;
                }
            }
        }

        return (*this);
    }

    Iterator operator++(int){
        Iterator old(*this);
        ++(*this);
        return old;
    }
    bool operator==(const Iterator& rhs){
        return &tree_ == &(rhs.tree_) && iter_ == rhs.iter_;
    }
    bool operator!=(const Iterator& rhs){
        return &tree_ != &(rhs.tree_) || iter_ != rhs.iter_;
    }
    auto operator*() -> Pair<Key, Value> {
        return Pair<Key, Value>(iter_->key, iter_->val);
    }
private:
    RBTree<Key, Value>& tree_;
    Node* iter_ = nullptr;
    std::list<Node*> visit_stack;
    bool check_right = true;
};

#endif // RB_TREE_H_
