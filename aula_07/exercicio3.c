#include <stdio.h>

int main()
{
    float array[8], Max, Min, pos_min, pos_max;
    for(int i = 0; i < 8; i++)
    {
        printf("Digite o numero %d: ", i+1);
        scanf("%f", &array[i]);
    }

    Min = array[0];
    Max = array[0];

    for(int i = 0; i < 8; i++)
    {
        if(array[i] > Max)
        {
            Max = array[i];
            pos_max = 1+i;
        }
        else if (array[i] < Min)
        {
            Min = array[i];
            pos_min = 1+i;
        }
    }
    printf("\nO maior Numero é: %2.f", Max);
    printf("\nPosiçao do maior %2.f", pos_max);
    printf("\nO menor Numero é: %2.f", Min);
    printf("\nPosiçao do menor %2.f", pos_min);

    
    
    return 0;


}