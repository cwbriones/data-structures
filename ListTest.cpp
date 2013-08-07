#include "List.h"

#include <iostream>

int main(int argc, const char *argv[])
{
    List<int> list;
    list.append(2);
    list.prepend(1);
    list.append(3);
    list.prepend(0);

    auto runner = list.head();
    while (runner){
        std::cout << runner->data << std::endl;
        runner = runner->next;
    }

    return 0;
}
