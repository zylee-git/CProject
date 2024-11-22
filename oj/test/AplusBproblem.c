#include <stdio.h>

int main()
{
    int result = 0, l1, l2, i, x = 0;
    char c;
    int n1[1000] = {0}, n2[1000] = {0}, n3[1001] = {0};
    for (l1 = 0; l1 < 1000; l1++) // get number1
    {
        c = getchar();
        if (c == ' ')
            break;
        else
            n1[l1] = c - '0';
    }
    for (l2 = 0; l2 < 1000; l2++) // get number2
    {
        c = getchar();
        if (c == '\n')
            break;
        else
            n2[l2] = c - '0';
    }
    if (l1 == 1 && l1 == 1 && n1[0] == 0 && n2[0] == 0)
        printf("0");
    if (l1 < l2)
    {
        for (i = 0; i < l1; i++)
        {
            n3[1000 - i] += n1[l1 - 1 - i] + n2[l2 - 1 - i];
            if (n3[1000 - i] >= 10)
            {
                n3[1000 - i] -= 10;
                n3[999 - i] += 1;
            }
        }
        for (i = l1; i < l2; i++)
        {
            n3[1000 - i] += n2[l2 - 1 - i];
            if (n3[1000 - i] >= 10)
            {
                n3[1000 - i] -= 10;
                n3[999 - i] += 1;
            }
        }
    }
    else
    {
        for (i = 0; i < l2; i++)
        {
            n3[1000 - i] += n1[l1 - 1 - i] + n2[l2 - 1 - i];
            if (n3[1000 - i] >= 10)
            {
                n3[1000 - i] -= 10;
                n3[999 - i] += 1;
            }
        }
        for (i = l2; i < l1; i++)
        {
            n3[1000 - i] += n1[l1 - 1 - i];
            if (n3[1000 - i] >= 10)
            {
                n3[1000 - i] -= 10;
                n3[999 - i] += 1;
            }
        }
    }
    for (i = 0; i < 1001; i++)
    {
        if (n3[i])
            x = 1;
        if (x)
            printf("%d", n3[i]);
    }
    printf("\n");
}