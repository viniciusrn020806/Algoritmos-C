#include <stdio.h>
#include <math.h> 

int main(){
    
    float media, lab, lab01, lab02, lab03, nota2, nota3;

    printf("Digite a nota do seu lab01: ");
    scanf("%f", &lab01);

    printf("Digite a nota do seu lab02: ");
    scanf("%f", &lab02);

    printf("Digite a nota do seu lab03: ");
    scanf("%f", &lab03);
    
    printf("Digite sua nota2: ");
    scanf("%f", &nota2);

    printf("Digite sua nota3: ");
    scanf("%f", &nota3);

    lab = (lab01 + lab02 + lab03) / 3;
    
    media = (0.2 * lab) + (0.8 * sqrt(nota2 * nota3));
    printf("A NF é: %.2f\n ",media);
    
    return 0;
    


}