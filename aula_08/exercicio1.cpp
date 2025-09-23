#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  int Conta_Caracteres(char *s, char c)
    {
        int count = 0;
        for(int i = 0; s[i] != '\0'; i++)
        {
            if(s[i] == c)
            count++;
        }
        return count;
    }
   
   void inverte_string(char *s)
   {
    char *inicio = s;
    char *fim = s + strlen(s) - 1;
    char temp;
    while(inicio < fim)
    {
        char temp = *inicio;
       temp = *inicio;   // guarda o caractere inicial
        *inicio = *fim;   // copia o final para o início
        *fim = temp;      // copia o inicial guardado para o final

        inicio++;
        fim--;

    }
   }

    int main()
{
    char s[] = "Banana";
    printf("%s\n", s);
    inverte_string(s);
    printf("%s\n", s);


    return 0;
}