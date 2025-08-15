#include <stdio.h>

int main() {
    // Mensagem de teste
    printf("Ola, mundo!\n");

    // Teste de leitura de dados
    char nome[50];
    int idade;

    printf("Digite seu nome: ");
    scanf("%49s", nome);

    printf("Digite sua idade: ");
    scanf("%d", &idade);

    printf("Prazer, %s! Voce tem %d anos.\n", nome, idade);

    return 0;
}
