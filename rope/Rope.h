#ifndef ROPE_H
#define ROPE_H

#include <string>
#include <memory>

class Rope
{
public:
    Rope();
    Rope(const std::string& str);
    ~Rope();

    const size_t size() const;
    std::string to_str() const;
private:
    class Node {
    public:
        Node();
        Node(const std::string& str);
        ~Node();

        const size_t weight() ;
        std::string str() const;
    private:
        Node* left_;
        Node* right_;

        bool dirty_;
        size_t weight_;
        std::string data_;

        const size_t MIN_STR_LENGTH = 6;
    };

    Node* head_;
};

#endif /* ROPE_H */
