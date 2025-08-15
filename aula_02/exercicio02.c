#include <stdio.h>

int main(){
    int hora;
    int minuto;
    int segundo;
    int tempo_passado;
    int segundos_meia;
    int segundos_faltam;
    
    
    printf("Digite a hora: ");
    scanf("%d", &hora);
    
    printf("Digite o minuto: ");
    scanf("%d", &minuto);

    printf("Digite os segundos: ");
    scanf("%d", &segundo);

    tempo_passado = (hora * 3600) + (minuto * 60) + segundo;
    segundos_meia = (24 * 3600);

    
    printf("Se passaram %d segundos desde 00:00: passaram segundos", tempo_passado);
    printf("Faltam %d segundos para 00:00: ", (segundos_meia - tempo_passado));


}