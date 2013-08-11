#ifndef TRIE_H
#define TRIE_H 

#include <iostream>

template <class Value>
class Trie {
public:
    Trie();
    ~Trie();
    void put(std::string key, Value val);
    Value* get(std::string key);
private:
    struct Node {
        Node(int radix) {
            next_ = new Node* [radix];
            for (int r = 0; r < radix; r++){
                next_[r] = nullptr;
            }
        }
        ~Node(){
            delete[] next_;
        }
        Value* val_ = nullptr;
        Node** next_ = nullptr;
    };
    Node* root_ = nullptr;
    const int radix_ = 256;

    Node* get(Node* root, std::string key, int d);
    Node* put(Node* root, std::string key, Value val, int d);
    void clear(Node* root);
};

template <class value>
Trie<value>::Trie(){}

template <class value>
Trie<value>::~Trie(){
    clear(root_);
}

template <class value>
void Trie<value>::clear(Node* root){
    if(!root){
        return;
    }

    for (int i = 0; i < radix_; i++){
        clear(root->next_[i]);
    }
    delete root;

    return;
}

template <class Value>
Value* Trie<Value>::get(std::string key){
    auto result = get(root_, key, 0);
    if (result){
        std::cout << "Result non-null" << std::endl;
        return result->val_;
    }
    return nullptr;
}

template <class Value>
typename Trie<Value>::Node* Trie<Value>::get(Node* root, std::string key, int d){
    if (!root){
        return nullptr;
    }
    if (d == key.size()){
        return root;
    }
    return get(root->next_[ key[d] ], key, d+1);
}

template <class Value>
void Trie<Value>::put(std::string key, Value val){
    root_ = put(root_, key, val, 0);
}

template <class Value>
typename Trie<Value>::Node* Trie<Value>::put(Node* root, std::string key, Value val, int d){
    if (!root) {
        root = new Node(radix_);
    }
    if (d == key.size()){
        root->val_ = new Value(val);
    }
    else {
        root->next_[key[d]] = put(root->next_[key[d]], key, val, d+1);
    }
    return root;
}

#endif
