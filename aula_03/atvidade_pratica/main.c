#include <stdio.h>
#include "calculadora.h"

int main(){
    char opcao;
    float num1, num2, resultado;
    printf("digite S para somar, D para dividir e M para subtrair\n");
    scanf("%c", &opcao);

    printf("Digite o primeiro numero\n");
    scanf("%f", &num1);
    
    printf("Digite o segundo numero\n");
    scanf("%f", &num2);

    if (opcao == 'S' || opcao == 's'){
        resultado = soma(num1, num2);
    printf("O resultado da soma é: %.2f", resultado);


    }



    
    
    
    
    return 0;
}