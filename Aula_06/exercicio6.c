#include <stdio.h>

int f_rec(int x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    return f_rec(x, n - 1) * x;
}

int f_inter(int x, int n)
{
    int res = 1;
    for(int i = 0; i < n; i++)
    {
        res *= x;
    }
    return res;
}

int main()
{
    printf("Recursivo %d\n", f_rec(2,4));
    printf("Interativo %d\n", f_inter(2,4));
    
    return 0;
}