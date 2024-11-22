#ifndef LINKLIST_H

#define LINKLIST_H

#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

class LinkList
{
public:
    LinkList(); // Construct
    //~LinkList();                            // Destruct
    bool clearSqList();                           // Clear LinkList
    bool IsEmpty() { return head->next == NULL; } // Whether empty
    int Length();                                 // Get length
    bool GetElem(int i, int **e);                 // Get element
    int LocateElem(int e);                        // Locate element
    bool PriorElem(int cur_e, int **pre_e);       // Get previous element
    bool NextElem(int cur_e, int **next_e);       // Get next element
    bool Insert(int i, int e);                    // Insert an element
    bool Delete(int i, int **e);                  // Delete an element
    bool Traverse(bool (*visit)(int e));

private:
    Node *head;
};

#endif // LINKLIST_H