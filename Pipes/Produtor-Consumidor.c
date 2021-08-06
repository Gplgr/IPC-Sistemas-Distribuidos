#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/* Principal referencia:
    https://www.geeksforgeeks.org/pipe-system-call/
*/
int conduite[2], i, n;
int valorenviado = 0;
char enviado[20];
int valorrecebido = -1;
char recebido[20];

void main(){
    char *primo = malloc(256);
    int verificador;
    srand(time(NULL));
    if (pipe(conduite) < 0) exit(1);
    // Trecho do processo filho (produtor)
    if (fork() == 0) {
        printf("no processo produtor\n");
        printf("Insira o numero de numeros que serao produzidos: ");
        scanf("%d",&n);
        for (i=0;i<n;i++){
            valorenviado = valorenviado + rand()%100+1;
            sprintf(enviado,"%d",valorenviado);
            write(conduite[1],enviado,20);
        };
        sprintf(enviado,"%d", 0);
        write(conduite[1], enviado, 20);
        wait(NULL);
    }

    //Trecho do processo pai (consumidor)
    else {
        printf("no processo consumidor\n");
        while((verificador = read(conduite[0], recebido, 20))>0) {
            valorrecebido = atoi(recebido);
            if (valorrecebido==0) exit(0);;
            strcpy(primo,"e primo");
            if (valorrecebido==1) strcpy(primo,"nao e primo");
            for (int j=2;(double)j <= sqrt(valorrecebido); j++){
                if (valorrecebido%j == 0){
                    strcpy(primo,"Nao e primo");
                };
            };
            printf("Em relacao a %d: %s\n", valorrecebido,primo);
        };
        if (verificador != 0) exit(2);
    };
};
