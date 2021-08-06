#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void main (){
    int pid, sig, killcheck;
    do {
        sleep(0.2);
        printf("Insira o pid do processo alvo: ");
        scanf("%d", &pid);
        printf("Insira o sinal desejado: ");
        scanf("%d", &sig);
        printf("\n");
        killcheck = kill(pid,0);
        if  (killcheck) {
            printf("nao existe processo com esse pid, tente novamente\n");
        }
    } while (killcheck);
    kill(pid,sig);
    printf("Sinal enviado\nSaindo");
}  