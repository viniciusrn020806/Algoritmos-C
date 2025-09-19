#include <stdio.h>

int main()
{
    float Numeros[10], Soma = {0.0f};
    
    for(int i = 0; i < 10; i++)
    {
        printf("Digite o numero %d: ", i+1);
        scanf("%f", &Numeros[i]);
        Soma += Numeros[i];
    }
    printf("\nA soma de 10 numeros é: %.2f",  Soma);

    return 0;
}