#include <stdio.h>

#define MOD 9973

typedef struct
{
    int m[2][2];
} Matrix;

Matrix multiply(Matrix a, Matrix b)
{
    Matrix result;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            result.m[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
                result.m[i][j] %= MOD;
            }
        }
    }
    return result;
}

Matrix matrix_pow(Matrix base, int n)
{
    Matrix result = {{{1, 0}, {0, 1}}};
    while (n > 0)
    {
        if (n & 1)
        {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        n >>= 1;
    }
    return result;
}

int fibonacci(int n)
{
    if (n == 0)
        return 0;
    Matrix base = {{{1, 1}, {1, 0}}};
    Matrix result = matrix_pow(base, n - 1);
    return result.m[0][0];
}

int main()
{
    int n, i;
    int origin[20];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &origin[i]);
    for(i = 0; i < n; i++)
        printf("%d\n", fibonacci(origin[i]));
    return 0;
}
