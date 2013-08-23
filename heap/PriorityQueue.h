#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "Heap.h"

template <class T>
class PriorityQueue {
public:
    PriorityQueue(){}
    ~PriorityQueue(){}
    void enqueue(T item, int priority=0){
        QueueItem qitem(priority, item);
        items_.insert(qitem);
    }
    T dequeue(){
        QueueItem item = items_.pop_min();
        return item.value;
    }
    bool is_empty(){
        return items_.size() == 0;
    }
private:
    struct QueueItem {
        QueueItem(){}
        QueueItem(int priority, T& value) : value(value){
            this->priority = priority;
        }
        int priority;
        T value;

        bool operator>(QueueItem& other){
            return this->priority > other.priority;
        }
        bool operator<(QueueItem& other){
            return this->priority < other.priority;
        }
    };
    MinHeap<QueueItem> items_;
};

#endif // PRIORITY_QUEUE_H_
