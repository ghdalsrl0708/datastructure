#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 8888

void error_handling(char *message);
void menu();

int main(int argc, char **argv) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFSIZE];
    char menumessage[BUFSIZE];
    int str_len;

    if (argc != 2) {
        printf("Usage : %s <IP>", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    while (1) {
        menu();
        fgets(message, BUFSIZE, stdin);
        if (strcmp(message, "!menu\n") == 0) {
            fgets(menumessage, BUFSIZE, stdin);
            write(sock, menumessage, strlen(menumessage));
        } else
            write(sock, message, strlen(message));
    }
    close(sock);
    return 0;
}

void menu() {
    system("clear");
    printf(" ********* simple hacking TOol *********\n");
    printf(" ****** menu *****************\n");
    printf(" if you want to select menu -> !menu\n");
    printf(" 1. randsome ware\n");
    printf(" 2. ps\n");
    printf(" 3. getuid\n");
    printf(" ******************************\n");
    // printf(" Exit -> q & Q \n\n");
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
