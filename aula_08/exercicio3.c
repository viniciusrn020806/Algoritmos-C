#include <stdio.h>
#include <string.h>
#include <ctype.h>

void limpa_string(char *str)
{   
    int i, tam; 
    tam = strlen(str);
    int j = 0;

    for (i = 0; i < tam; i++)   // antes estava só "tam", causando loop infinito
    {   
        if (str[i] != ' ')      // remove apenas os espaços (como no seu)
        {
            str[j] = tolower((int)str[i]); // converte para minúsculo
            j++;
        }
    }
    str[j] = '\0'; // só termina a string no final
}

int eh_palindromo(char *str)
{
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right)
    {
        if (str[left] != str[right])
            return 0; // falso
        left++;
        right--;
    }
    return 1; // verdadeiro
}

int main()
{
    char s[] = "O  v  o";

    limpa_string(s);
    printf("Limpa: \"%s\"\n", s);

    if (eh_palindromo(s))
        printf("É palíndromo\n");
    else
        printf("Não é palíndromo\n");

    return 0;
}
