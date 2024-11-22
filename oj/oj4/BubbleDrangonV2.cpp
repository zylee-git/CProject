#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

typedef struct TNode *BinTree;
struct TNode
{
    unsigned short v;
    unsigned short nodecount;
    unsigned short vsum;
    BinTree l;
    BinTree r;
    TNode() : v(0), nodecount(1), vsum(0), l(NULL), r(NULL) {};
};

BinTree Build(unsigned short *pre, unsigned short *v, unsigned short *in, unsigned short n)
{
    stack<BinTree> st;
    stack<unsigned short> num;
    unsigned short i,cnode,cv;
    BinTree root = new TNode;
    root->v = v[0];
    root->vsum = v[0];
    st.push(root);
    num.push(pre[0]);
    unsigned short index = 0;
    for (i = 1; i < n; ++i)
    {
        BinTree node = st.top();
        if (num.top() != in[index])
        {
            node->l = new TNode;
            node->l->vsum = node->l->v = v[i];
            st.push(node->l);
            num.push(pre[i]);
        }
        else
        {
            while (!st.empty() && num.top() == in[index])
            {
                node = st.top();
                st.pop();
                num.pop();
                ++index;
            }
            node->r = new TNode;
            node->r->v = v[i];
            st.push(node->r);
            num.push(pre[i]);
        }
    }
    return root;
}

int main()
{
    unsigned short N, *pre, *in, *v, i;
    double final = 0;
    scanf("%hu", &N);
    pre = new unsigned short[N];
    in = new unsigned short[N];
    v = new unsigned short[N];
    for (i = 0; i < N; i++)
        scanf("%hu", pre + i);
    for (i = 0; i < N; i++)
        scanf("%hu", v + i);
    for (i = 0; i < N; i++)
        scanf("%hu", in + i);
    stack<BinTree> st;
    stack<unsigned short> num;
    unsigned short i;
    BinTree root = new TNode;
    root->v = v[0];
    st.push(root);
    num.push(pre[0]);
    unsigned short index = 0;
    for (i = 1; i < N; ++i)
    {
        BinTree node = st.top();
        if (num.top() != in[index])
        {
            node->l = new TNode;
            node->l->v = v[i];
            st.push(node->l);
            num.push(pre[i]);
        }
        else
        {
            while (!st.empty() && num.top() == in[index])
            {
                node = st.top();
                st.pop();
                num.pop();
                ++index;
            }
            node->r = new TNode;
            node->r->v = v[i];
            st.push(node->r);
            num.push(pre[i]);
        }
    }
    printf("%.2lf\n", final);
    // printf("%d\n", TotalWeight(root));
}