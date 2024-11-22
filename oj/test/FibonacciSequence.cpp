#include <stdio.h>
#include <vector>
using namespace std;

vector<int> v = {0, 1};

int fibonacci(int n)
{
    if (n >= v.size())
    {
        for (int i = v.size(); i <= n; i++)
        {
            v.push_back((v[i - 1] + v[i - 2]) % 9973);
        }
    }
    return v[n];
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int *a = new int[n];
    for (i = 0; i < n; i++)
    {
        scanf("%d", a + i);
    }
    for (i = 0; i < n; i++)
    {
        printf("%d\n", fibonacci(a[i]));
    }
}