#include "LinkList.h"

LinkList::LinkList()
{
    head = (Node *)new Node[1];
    head->next = NULL;
}
bool LinkList::GetElem(int i, int **e)
{
    Node *p = head;
    int j = 0;
    if ((*this).IsEmpty())
        return -1;
    p = p->next;
    while(p && j < i)
    {
        p = p->next;
        j++;
    }
    if(!p)
        return false;
    *e = new int(p->data);
    return true;
}
int LinkList::LocateElem(int e)
{
    Node *p = head;
    int i = 0;
    if ((*this).IsEmpty())
        return -1;
    p = p->next;
    while (p && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p)
        return i;
    else
        return -1;
}
bool LinkList::PriorElem(int cur_e, int **pre_e)
{
    Node *p = head, *q = new Node[1];
    return false;
}
bool LinkList::NextElem(int cur_e, int **next_e)
{
    return false;
}
bool LinkList::Insert(int i, int e)
{
    Node *p = head, *s;
    s = (Node *)new Node[1];
    int j = 0;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (j == i)
    {
        s->next = p->next;
        s->data = e;
        p->next = s;
        return true;
    }
    return false;
}