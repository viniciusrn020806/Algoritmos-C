#include <stdio.h>   // biblioteca padrão de entrada/saída (printf, etc.)
#include <string.h>  // biblioteca para manipulação de strings (strlen, etc.)
#include <ctype.h>   // biblioteca para funções de caractere (tolower, etc.)

// Função que "limpa" a string: remove espaços e transforma em minúsculas
void limpa_string(char *str)
{   
    int i, tam; 
    tam = strlen(str); // calcula o tamanho da string original
    int j = 0;         // índice para escrever a string "limpa"

    // percorre todos os caracteres da string
    for (i = 0; i < tam; i++)
    {   
        if (str[i] != ' ')  // se o caractere NÃO for espaço...
        {
            // converte para minúsculo (tolower) e guarda na posição "j"
            str[j] = tolower((int)str[i]);
            j++; // avança o índice de escrita
        }
        // se for espaço, apenas ignora
    }
    str[j] = '\0'; // finaliza a string corretamente com caractere nulo
}

// Função que verifica se uma string é palíndromo
int eh_palindromo(char *str)
{
    int left = 0;                  // índice do começo da string
    int right = strlen(str) - 1;   // índice do final da string

    // compara caracteres das extremidades até o meio
    while (left < right)
    {
        if (str[left] != str[right])
            return 0; // se algum par não for igual → não é palíndromo
        left++;   // avança do começo para o meio
        right--;  // recua do fim para o meio
    }
    return 1; // se todos os pares conferirem → é palíndromo
}

int main()
{
    // string de teste
    char s[] = "O  v  o"; 

    // chama a função que remove espaços e deixa tudo minúsculo
    limpa_string(s);

    // imprime a versão "limpa" da string
    printf("Limpa: \"%s\"\n", s);

    // verifica se é palíndromo e mostra o resultado
    if (eh_palindromo(s))
        printf("É palíndromo\n");
    else
        printf("Não é palíndromo\n");

    return 0; // fim do programa
}
