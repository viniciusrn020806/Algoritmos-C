#include <stdio.h>

int collatz(int n)
{
    if(n == 1)
    {
        return 0;
    }
    if(n % 2 == 0)
    {
       return collatz((int)(n / 2)) + 1;
    } 
    else
    {
        return collatz(3 * n + 1 ) + 1;
    }
}

int main()
{
    printf("%d\n ", collatz(3));
    return 0;
} 