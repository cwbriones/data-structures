#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
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

template <class Key, class Value>
class RBTree {
public:
    RBTree();
    ~RBTree();

    void put(Key key, Value val);
    Value* get(Key key);
    void clear();

    Key min();
    Key max();

    class Iterator;
    Iterator begin();
    Iterator end();
private:
    struct Node;

    Node* root_ = nullptr;
    Node* put(Node* root, Key key, Value val);
    Value* get(Node* root, Key key);

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
            if (iter_->key < iter->key){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            }
            else if (iter_->key > iter->key){
                iter_ = iter_->right;
            }
        }
    }

    Iterator(RBTree<Key, Value>& tree, Key key) : tree_(tree) {
        iter_ = tree.root_;
        while (iter_ && iter_->key != key){
            if (iter_->key < key){
                visit_stack.push_back(iter_);
                iter_ = iter_->left;
            }
            else if (iter_->key > key){
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

template <class Key, class Value>
RBTree<Key, Value>::RBTree(){}

template <class Key, class Value>
RBTree<Key, Value>::~RBTree(){
    clear();
}

template <class Key, class Value>
Key RBTree<Key, Value>::min(){
    
}

template <class Key, class Value>
Key RBTree<Key, Value>::max(){
}

template <class Key, class Value>
void RBTree<Key, Value>::clear(){
    clear_tree(root_);
    root_ = nullptr;
}

template <class Key, class Value>
void RBTree<Key, Value>::clear_tree(Node* root){
    if (!root){
        return;
    } else {
        clear_tree(root->left);
        clear_tree(root->right);
    }
    std::cout << "Deleting node: (" << root->key << ", " << root->val << ")" << std::endl;
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

template <class Key, class Value>
Value* RBTree<Key, Value>::get(Key key){
    return get(root_, key);
}

template <class Key, class Value>
Value* RBTree<Key, Value>::get(Node* root, Key key){
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

template <class Key, class Value>
void RBTree<Key, Value>::put(Key key, Value val){
    root_ = put(root_, key, val);
    root_->color = BLACK;
}

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

template <class Key, class Value>
void RBTree<Key, Value>::flip_colors(Node* node){
    node->left->color = BLACK;
    node->right->color = BLACK;

    node->color = RED;
}

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

template <class Key, class Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::put(Node* root, Key key, Value val){
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

#endif
