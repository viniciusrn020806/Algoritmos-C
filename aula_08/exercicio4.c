#include <stdio.h>
#include <string.h>

void formatar_nome(char * nome)
{   
    int i = 0;
    while(nome[i] == ' ')
    {
        nome[i] = nome[i + 1];
        i++;
    }
}


int main()
{
   char nome[]= "    Luciano";
   formatar_nome(nome);
   printf("%s", nome);
    return 0;
}