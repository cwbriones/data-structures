#ifndef ROPE_H
#define ROPE_H

#include <string>

class Rope
{
public:
    Rope();
    ~Rope();
    
private:
    class Node {
    public:
        Node();
        ~Node();
    private:
        Node* left;
        Node* right;

        size_t weight;
        std::string data;
    };
};

#endif /* ROPE_H */
