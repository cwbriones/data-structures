#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <random>

template <class Type>
class SkipList {
public:
    SkipList();
    void insert(Type item);
    bool contains(Type item);
private:
    class Node {
    public:
    private:
        Node** next;
    };
};

#endif // SKIP_LIST_H_
