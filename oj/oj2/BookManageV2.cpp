#include <iostream>
#include <sstream>
#define COUNT 100
using namespace std;

typedef struct NODE
{
    int ID;
    struct NODE *next;
    NODE()
    {
        ID = 0;
        next = NULL;
    }
    NODE(int id)
    {
        ID = id;
        next = NULL;
    }
} node;

void add(node *head, int ID) // add a book to the linklist
{
    node *temp = new node(ID);
    temp->next = head->next;
    head->next = temp;
    return;
}
int seekbook(node *head, int ID) // seek a book from the linklist
{
    node *p = head;
    while (p->next && p->ID != ID)
    {
        p = p->next;
    }
    if (p->ID == ID)
        return 1;
    return 0;
}
int borrowbook(node *head, int ID) // seek a book from the linklist
{
    node *pre = head, *p = pre->next;
    while (p->next && p->ID != ID)
    {
        pre = p;
        p = pre->next;
    }
    if (p->ID != ID)
        return 0;
    pre->next = p->next;
    delete p;
    p = NULL;
    return 1;
}
int returnbook(node *head, int ID)
{
    if (!seekbook(head, ID))
    {
        add(head, ID);
        return 1;
    }
    return 0;
}

int main()
{
    int tmp, m, i, op;
    string line, result;
    node* head[COUNT];
    for (i = 0; i < COUNT;i++)
    {
        head[i] = new node();
    }
    getline(cin, line);
    istringstream iss(line);
    while (iss >> tmp)
    {
        add(head[tmp%COUNT], tmp);
    }
    scanf("%d", &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &op, &tmp);
        switch (op)
        {
        case 1:
            result += to_string(seekbook(head[tmp%COUNT], tmp));
            break;
        case 2:
            result += to_string(borrowbook(head[tmp%COUNT], tmp));
            break;
        case 3:
            result += to_string(returnbook(head[tmp%COUNT], tmp));
            break;
        }
    }
    cout << result << endl;
}
