#include <stdio.h>
#include "calculadora.h"

int main(){
    char opcao;
    float num1, num2, resultado;
    printf("digite S para somar, D para dividir, B para subtrair e M para multiplicar\n");
    scanf("%c", &opcao);

    printf("Digite o primeiro numero\n");
    scanf("%f", &num1);
    
    printf("Digite o segundo numero\n");
    scanf("%f", &num2);

    if (opcao == 'S' || opcao == 's'){
        resultado = soma(num1, num2);
    printf("O resultado da soma é: %.2f", resultado);
}

  if (opcao == 'D' || opcao == 'd'){
        resultado = div(num1, num2);
        printf("O resultado da divisão é: %.2f", resultado);
      
}

    if (opcao == 'B' || opcao == 'b'){
        resultado = sub(num1, num2);
        printf("O resultado da subtração é: %.2f", resultado);
}
    if (opcao == 'M' || opcao == 'm'){
        resultado = multi(num1, num2);
        printf("O resultado da multiplicação é: %.2f", resultado);
    }
    else{
        return printf("Opção Inválida!");
    }
    return 0;
}