#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int i = 0, tipo = 2;;
/* avaliar busy wait e blocking wait!!! */
void handler(int sig){
    if(sig == SIGTERM){
        i=0;
        printf ("Voltamos a estaca zero\n");
    }
    if(sig == SIGUSR1){
        printf("Iniciando a autodestruicao\n");
        raise(SIGKILL);
    } 
    if(sig == SIGUSR2){
        i=i+720;
        printf("A maquina do tempo avancou 10min\nPassamos para %d segundos\n",i*5);
    }
}

void main () {
    /* Definindo os sinais a serem tratados */
    signal(SIGTERM, handler);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    /*
    Se tipo for 0 --> blocking wait
    Se tipo for 1 --> busy wait
    */
    while (tipo != 0 && tipo != 1){
        printf ("Insira 0 para blocking wait e 1 para busy wait: ");
        scanf ("%d", &tipo);
    };
    printf("O numero do processo e %d\n", getpid());
    if (tipo){
        for (i;;i++){
            printf("Este programa esta rodando ha %d segundos\n", i*5);
            sleep(5);
        };
    }
    else {while (1){pause();};};
}