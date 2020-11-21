/**
By: SaySeven
**/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    
    if(argc <= 1){
        printf("Ex: ./portscan 192.168.0.1\n");
        return 0;
    }
    
    struct sockaddr_in alvo;
    struct hostent *host = gethostbyname(argv[1]);
    if(host == NULL){
        printf("Ocorreu um erro com a estrutura host :(\n");
        exit(1);

    }

    int socket_fd;
    int net;
    int count;
    int topport[] = {21,22,23,80,110,443,3306,8080};
    int porta;

    printf("IP: %s\n", inet_ntoa(*((struct in_addr *)host->h_addr)));

    for(porta=0;porta<sizeof(topport);porta++){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    alvo.sin_family = AF_INET;
    alvo.sin_port = htons(topport[porta]);
    alvo.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)host->h_addr)));

    net = connect(socket_fd, (struct sockaddr *)&alvo, sizeof(alvo));
    if(net == 0){
        printf("Porta %d -status [ABERTA]\n", topport[porta]);
        close(net);
        close(socket_fd);
        close(host);
    }
    }
    return 0;
    
}