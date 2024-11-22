#include "LinkList.h"
#include <iostream>

int main()
{
    LinkList l;
    int *num;
    for (int i = 0; i < 5;i++)
    {
        l.Insert(i, i);
    }
    if (l.GetElem(9, &num))
        std::cout << *num << std::endl;
    std::cout << l.IsEmpty() << std::endl;
}