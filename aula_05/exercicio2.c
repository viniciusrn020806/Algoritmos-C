#include <stdio.h>

int main(){
    float nota1, nota2, nota3, media;


    printf("Digite a sua nota1");
    scanf("%f", &nota1);

    printf("Digite a sua nota2");
    scanf("%f", &nota2);

    printf("Digite a sua nota3");
    scanf("%f", &nota3);

    media = (nota1 + nota2+ nota3) /3;

    if (media >= 7.00){
        return printf("Você foi Aprovado!!");
    }
    else if(media >=5 ){
        return printf("Você ficou de rec!!!!!");

    } 
    else if(media < 5 ){
        return printf("Você foi Reprovado !!!!!");

    } 
    return 0;
}