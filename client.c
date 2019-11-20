#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define PORT 9999
#define IP "127.0.0.1"

void error_handling(char *message);

int main(int argc, char **argv) {

    int sock;
    char menu[BUFSIZE];
    char filename[BUFSIZE];
    char buf[100];
    char temp[20];
    char *f;
    int size;
    int filehandle;
    int status;
    struct stat obj;

    struct sockaddr_in serv_addr;

    if (argc != 2) {
        printf("Usage : %s <IP>", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(atoi(argv[1]));
    //제출할 때 PORT 바꿔야함 -> PORT

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    //실제 실행 부분
    while (1) {
        printf("\033[1;33m ex command \n");
        printf("\033[1;33m download, upload, pwd, ls, cd, quit\n");
        printf("\033[1;32m HackToOl command line > ");
        fgets(menu, BUFSIZE, stdin); // command
        fprintf(stderr, "\033[97m"); // white

        if (!strcmp(menu, "download\n")) { // download
            printf("다운로드할 파일 : ");
            scanf("%s", filename);
            fgets(temp, BUFSIZE, stdin); //버퍼에 남은 엔터 제거
            strcpy(buf, "download ");
            strcat(buf, filename);
            send(sock, buf, 100, 0);
            recv(sock, &size, sizeof(int), 0);
            if (!size) {
                printf("파일이 존재하지 않습니다.");
                continue;
            }
            f = malloc(size);
            recv(sock, f, size, 0);
            while (1) {
                filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
                if (filehandle == -1) {
                    sprintf(filename + strlen(filename), "_1");
                } else {
                    break;
                }
            }
            write(filehandle, f, size, 0);
            close(filehandle);
            printf("다운로드 완료\n");
        } else if (!strcmp(menu, "upload\n")) { // upload
            printf("업로드할 파일 : ");
            scanf("%s", filename);
            fgets(temp, BUFSIZE, stdin);
            filehandle = open(filename, O_RDONLY);
            if (filehandle == -1) {
                printf("파일이 없습니다.\n");
                continue;
            }
            strcpy(buf, "upload ");
            strcat(buf, filename);
            send(sock, buf, 100, 0);
            stat(filename, &obj);
            size = obj.st_size;
            send(sock, &size, sizeof(int), 0);
            sendfile(sock, filehandle, NULL, size);
            recv(sock, &status, sizeof(int), 0);
            if (status)
                printf("업로드 완료\n");
            else
                printf("업로드 실패\n");
        }
    }
    //여기까지
    close(sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
