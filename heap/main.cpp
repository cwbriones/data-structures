#include "Heap.h"
#include "PriorityQueue.h"

#include <iostream>
#include <string>

int main(int argc, const char *argv[])
{
    PriorityQueue<std::string> queue;
    queue.enqueue("Dog", 11);
    queue.enqueue("Cat", 5);
    queue.enqueue("Parrot", 12);
    queue.enqueue("Monkey", 1);

    while (!queue.is_empty()){
        std::cout << queue.dequeue() << std::endl;
    }

    return 0;
}
