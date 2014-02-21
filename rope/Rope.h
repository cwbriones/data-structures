#ifndef ROPE_H
#define ROPE_H

#include <string>
#include <memory>

class Rope
{
public:
    Rope();
    Rope(const Rope& left, const Rope& right);
    Rope(const std::string& str);
    
    size_t size() const;
    std::string to_str() const;
    char at(size_t pos) const;

    Rope&& concat(const Rope& other);
private:
    class Node {
    public:
        Node();
        Node(const std::string& str);
        Node(std::shared_ptr<Node> const& left, 
             std::shared_ptr<Node> const& right, size_t weight);
        
        std::string str() const;
        char at(size_t pos) const;
    private:
        std::shared_ptr<const Node> left_;
        std::shared_ptr<const Node> right_;

        size_t weight_;
        std::string data_;

        const size_t MIN_STR_LENGTH = 5;
    };

    std::shared_ptr<const Node> head_;
    const size_t size_;
};

#endif /* ROPE_H */
