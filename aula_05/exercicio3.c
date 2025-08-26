#include <stdio.h>

int main()
{
    int idade, MaiorIdade, MenorIdade;
    printf("Digite sua idade: ");
    scanf("%d", &idade);

  (idade >= 18) ? printf("\nVocê é maior de idade!!!"), MaiorIdade = idade : printf("\nVocê é menor de idade!!!"), MenorIdade = idade;


}