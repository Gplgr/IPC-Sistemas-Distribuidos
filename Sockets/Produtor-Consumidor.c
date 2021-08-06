#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* Principal referência:
https://www.educative.io/edpresso/how-to-implement-tcp-sockets-in-c
*/

int valorenviado = 0;
int valorrecebido = -1;

void main () {
    srand(time(NULL));
    if (fork() ==0) {
        int socket_desc, i, n;
        struct sockaddr_in server_addr;
        char server_message[20], client_message[20];

        //Esse sleep existe pra garantir que de tempo pro servidor configurar
        sleep(1);

        // Limpando buffers
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Criando o socket e configurando no IP 127.0.0.1 e na porta 
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        // Solicitando conexao ao servidor
        connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("Cliente conectado ao servidor\n");
        
        // Trecho tirado do exercicio de Pipes e editado
        printf("Insira o numero de numeros que serao produzidos: ");
        scanf("%d",&n);
        for (i=0;i<n;i++){
            valorenviado = valorenviado + rand()%100+1;
            sprintf(client_message,"%d",valorenviado);
            send(socket_desc, client_message, strlen(client_message), 0);
            recv(socket_desc, server_message, sizeof(server_message), 0);
            printf("Em relacao ao numero %d: %s\n",valorenviado,server_message);
        };
        sprintf(client_message,"%s", "0000000000000000000");
        send(socket_desc, client_message, strlen(client_message), 0);
        
        // Encerrando
        close(socket_desc);

    }
    else {
        printf("no processo servidor\n");
        int socket_desc, client_sock, client_size;
        struct sockaddr_in server_addr, client_addr;
        char primo[20], recebido[20];
        
        memset(primo, '\0', sizeof(primo));
        memset(recebido, '\0', sizeof(recebido));
    
        // Criando o socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        printf("Socket criado\n");
        
        // Configurando IP e porta
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
        listen(socket_desc, 1);
  
        // Aceitando conexao
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        printf("IP: %s porta: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        
        // Processando mensagem
        while (valorrecebido != 0) {
            recv(client_sock, recebido, sizeof(recebido), 0);
            valorrecebido = atoi(recebido);
            if (valorrecebido==0) exit(0);;
            strcpy(primo,"Esse e primo");
            if (valorrecebido==1) strcpy(primo,"Nao e primo!");
            for (int j=2;(double)j <= sqrt(valorrecebido); j++){
                if (valorrecebido%j == 0){
                    strcpy(primo,"Nao e primo!");
                };
            };
            send(client_sock, primo, strlen(primo), 0);
        };

        
        // Encerrando
        close(client_sock);
        close(socket_desc);
    };

};