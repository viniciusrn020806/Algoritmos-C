#include <stdio.h>
#include <string.h>

void formatar_nome(char * nome)
{   
    int i = 0, j = 0;
    while(nome[i] == ' ')
    {
        nome[i] = nome[i + 1];
        i++;
    }
    while(nome[j] != '\0')
    {
        nome[j] = nome[i];
        j++;
        i++;
    }
    nome[j] = '\0';

    i = 0;
    while(nome[i] != ' ')
    { 
        i++;
    }
    j = i + 1; 
    while(nome[j] == ' ' )
    {
        j++;
    }
    while(nome[j] != '\0')
    {
        nome[i + 1] = nome[j];
        i++;
        j++;
    }
    nome[i + 1] = '\0';
}


int main()
{
   char nome[]= "    Luciano             Rossi  ";
   formatar_nome(nome);
   printf("%s", nome);
    return 0;
}