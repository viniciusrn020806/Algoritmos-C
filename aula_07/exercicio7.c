#include <stdio.h>

int main()
{
    int matriz[4][4], num, linhas[] = {0, 0, 0, 0}, colunas[] = {0, 0, 0, 0};
    for(int linha = 0; linha < 4; linha++)
    {
         
        for (int coluna = 0; coluna < 4; coluna++)
        {
            scanf("%d", &num);
            matriz[linha][coluna] = num;
            linhas[linha] += num;
            colunas[coluna] += num;
        }
        
    }
    for(int i = 0; i < 4; i++)
    {
        printf("Linha %d: %d\n", i + 1, linhas[i]);
        printf("Coluna %d: %d\n", i + 1, colunas[i]);
    }
   
    return 0;
}