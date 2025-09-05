#include <stdio.h>

int main()
{
    int num, contador = 0, acumulador = 0;
    while (1)
    {
        do{
            printf("Digite um numero: ");
            scanf("%d", &num);
        } while (num < 0 || num > 100);
        if(num == 0)
        {
            break;
        }
        acumulador += num;
        contador++;

    }
    printf("A media é %.2f\n", (float)(acumulador / contador));
    return 0;
    
}