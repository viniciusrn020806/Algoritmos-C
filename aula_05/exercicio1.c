#include <stdio.h>

int main()
{
    int MaiorNumero, numero1, numero2;
    printf("\nDigite o numero 1: ");
    scanf("%d", &numero1);
    printf("\nDigite o numero 2: ");
    scanf("%d", &numero2);

    MaiorNumero = (numero1 > numero2) ? numero1 : numero2;
    if (numero1 == numero2){
        return printf("\nOs Numeros sao Iguais!!");
    }
    printf("\nO maior numero é: %d ", MaiorNumero);
    return 0;

}


