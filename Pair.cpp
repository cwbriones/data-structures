#include <iostream>

template <typename type1, typename type2>
struct Pair {
    type1 first;
    type2 second;
};

template <typename T, typename U>
Pair<T, U> make_pair(T first, U second){
    Pair<T, U> value;

    value.first = first;
    value.second = second;

    return value;
}

int main(int argc, const char *argv[])
{
    auto pair = make_pair(1, "HELLO!");    
    std::cout << pair.first << std::endl;
    std::cout << pair.second << std::endl;
    return 0;
}
