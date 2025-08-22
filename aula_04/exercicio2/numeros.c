int eh_par(int numero){
    if (numero % 2 == 0){
        return 1;
    }
    return 0;
}

int primo(int numero){
    for(int i = 2; i < numero; i++){
        if(numero % i == 0){
            return 0;
        }
    }
    return 1;
}

int calc_vetorial(int numero){
    int fatorial = 1;
    for(int i = 1; i <= numero; i++){
        fatorial = fatorial * i;
    }
    return fatorial;
   
}

int maior(int num1, int num2){
    if(num1 >= num2){
        return 1;
    }
    return num2;
}

int potencia(int base, int expo){
    int pot = 1;
    for(int i = 1; i <= expo; i++){
        pot = pot * base;
    }
    return pot;
}