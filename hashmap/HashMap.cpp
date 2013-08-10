#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <functional>

template <typename Key>
class Hash {
public:
    Hash(){};
    unsigned int operator()(Key k){ return hash(k); };
};

template <>
class Hash<int> {
    public:
        Hash(){};
        unsigned int operator()(int k){ 
            return k & 0x7fffffff; 
        };
};

template <>
class Hash<std::string> {
    public:
        Hash(){};
        unsigned int operator()(std::string k){
            int hash = 5381;

            for (auto& chr : k){
                // hash = (hash * 33) + c
                hash = ((hash << 5) + hash) + chr;
            }
            return hash & 0x7fffffff;
        };
};

template <typename T>
struct Bucket {
    T data;
    bool empty = true;
};

// Hash implemented with separate chaining
template <typename Key, typename Value>
class HashMapSC {
    public:
        HashMapSC(){
            m_ = 977;
        };

        HashMapSC(int m){
            m_ = m;
        };

        void put(Key key, Value value){

        };

        Value get(Key key){

        };

        bool contains(Key key){

        }
    private:
        int n_ = 0;
        int m_ = 997;
        Hash<Key> hashcode;
};

// Hash implemented with linear probing
template <typename Key, typename Value>
class HashMap {
public:
    HashMap(){
        keys_.reserve(m_);
        values_.reserve(m_);

        //Initialize
        for(int i = 0; i < m_; i++){
            keys_.push_back(Bucket<Key>());
            values_.push_back(Value());
        }
    };

    void put(Key key, Value value){
        if (n_ >= m_/2){
            resize(m_ * 2);
        }

        int i = hashcode(key) % m_;
        for(; !keys_[i].empty; i = (i + 1) % m_){
            if (keys_[i].data == key){
                values_[i] = value;
                return;
            }
        }
        keys_[i].data = key;
        keys_[i].empty = false;
        values_[i] = value;
        n_++;
    };

    Value* get(Key key){
        for(int i = hashcode(key) % m_; !keys_[i].empty; i = (i + 1) % m_){
            if (keys_[i].data == key){
                return &(values_[i]);
            }
        }
        return nullptr;
    };

    bool hasKey(Key key){
        for(int i = hashcode(key)% m_; !keys_[i].empty; i = (i + 1) % m_){
            if (keys_[i].data == key){
                return true;
            }
        }
        return false;
    };
private:
    int n_ = 0; // Number of key-value pairs
    int m_ = 16; // size of linear-probing table

    void resize(int newSize){
        
    };
    
    Hash<Key> hashcode;
    std::vector< Bucket<Key> > keys_;
    std::vector<Value> values_;
};

int main(int argc, const char *argv[])
{
    HashMap<std::string, int> map;
    map.put("Doggy", 15);
    std::cout << map.hasKey("Doggy") << std::endl;

    return 0;
}
