#include <stdio.h>
#include <math.h>




int main()
{
      int numeros = 0;

    do
   {
   
   
    float raio, area, base, altura;   
    
  
     printf("******************************\n");
    
    printf("1) Calcular a área do círculo;");
    printf("\n2) Calcular a área do retangulo;");
    printf("\n3) Calcular a área do trianfulo;");
    printf("\n4)Sair ;");
    printf("\nEscolha uma opcao: ");
         
    printf("\n******************************\n");
    printf("\nEscolha uma opcao: ");
    if (scanf("%d", &numeros) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            while (&getchar);
    }

 
    switch (numeros)
    {
    case 1 :   
        printf("\nDigite o raio do circulo: ");
        scanf("%f", &raio);
        area = M_PI * pow(raio, 2);
        printf("A area do circulo de raio %.2f eh: %.2f\n", raio, area);
   break;

    case 2 :  
        printf("\nDigite a base do retangulo: ");
        scanf("%f", &base);
        printf("\nDigite a altura do retangulo: ");
        scanf("%f", &altura);
        area = (base * altura);
        printf("\nA area do retangulo de base %.2f e altura %.2f eh: %.2f\n", base, altura, area);
    break;

    case 3 :   
        
        printf("\nDigite a base do triangulo: ");
        scanf("%f", &base);
        printf("\nDigite a altura do triangulo: ");
        scanf("%f", &altura);
        area = (base * altura) / 2.0;
        printf("A area do triangulo de base %.2f e altura %.2f eh: %.2f\n", base, altura, area);

    break;

    case 4 :   
        printf("\nSaindo do Programa... ");
        
    break;
    default: printf("Você nao digitou o numero certo!!!");
        break;
    }
  } while (numeros != 4);
  
   
  
    
   
  return 0;

}




