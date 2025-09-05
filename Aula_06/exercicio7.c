#include <stdio.h>

int f_iter(int n)
{
    int x = 0;
    if(n == 1)
    {
        return x;
    } 
    int y = 1;
    if(n == 2)
    {
        return y;
    }
    int aux;
    for(int i = 0; i < n - 2; i++)
    {
        aux = y;
        y +=x;
        x = aux; 
    }
    return y;
}
int f_rec(int n)
{
    if(n == 1 || n == 2)
    {
        return n - 1;
    }
    return f_rec(n - 1) + f_rec(n - 2);
}

int main()
{
   // printf("iterativa %d\n", f_iter(40));
     printf("Recursiva %d\n", f_rec(40));
    return 0;
}