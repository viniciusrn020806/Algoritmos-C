#include <stdio.h>



int main()
{
    float num1, num2;
    char Operacao;
    printf("\nDigite Numero1: ");
    scanf("%f", & num1);
    printf("\nDigite Numero2: ");
    scanf("%f", & num2);
    printf("Qual operacao deseja efetuar? \n+ Adição \n- Subtração \n* Multiplicação ou \n/ Divisão?");
    printf("\n Digite sua opção: ");
    scanf("%c", &Operacao);

    switch (Operacao)
    {
    case '+':
     printf("\nSoma de Num1 + Num 2 = ", num1 + num2);
        break;
    case '-':
    printf("\nSubtração de Num1 - Num2 = " , num1 - num2);
        break;
    case '*':
    printf("\nMutiplicação de Num1 * Num2 = " , num1 * num2);
        break;  
    case '/': 
    printf("\nDivisão de Num1 / Num2 = ", num1 /num2);
        break;
    default :
    printf("\n Você não digitou um operador valido! ");
        break;
    }

return 0;

}