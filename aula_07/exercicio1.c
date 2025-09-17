#include <stdio.h>

int main()
{
    
    int array[5];
    printf("Digite 5 numeros: \n");
    for(int i = 0;i < 5; i++) {
        printf("Numero: %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    printf("\nVoce digitou:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    
    

   
  
    
    return 0;
}