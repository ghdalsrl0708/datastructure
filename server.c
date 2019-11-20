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

void error_handling(char *message);

int main(int argc, char **argv) {

    int serv_sock;
    int clnt_sock;

    char buf[100];
    char command[10];
    char filename[BUFSIZE];
    struct stat obj;
    int filehandle;
    int size;
    int i;
    int c;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);

    clnt_sock =
        accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

    if (clnt_sock == -1)
        error_handling("accept() error");

    //실제 실행될 부분
    while (1) {
        recv(clnt_sock, buf, 100, 0);
        sscanf(buf, "%s", command);
        if (!strcmp(command, "download")) {
            sscanf(buf, "%s%s", filename, filename);
            stat(filename, &obj);
            filehandle = open(filename, O_RDONLY);
            size = obj.st_size;
            if (filehandle == -1) {
                size = 0;
            }
            send(clnt_sock, &size, sizeof(int), 0);
            if (size) {
                sendfile(clnt_sock, filehandle, NULL, size);
            }
        } else if (!strcmp(command, "upload")) {
            int c = 0, len;
            char *f;
            sscanf(buf + strlen(command), "%s", filename);
            recv(clnt_sock, &size, sizeof(int), 0);

            while (1) {
                filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
                if (filehandle == -1) {
                    sprintf(filename + strlen(filename), "_1");
                } else
                    break;
            }
            f = malloc(size);
            recv(clnt_sock, f, size, 0);
            c = write(filehandle, f, size);
            close(filehandle);
            send(clnt_sock, &c, sizeof(int), 0);
        } else if (!strcmp(command, "ls")) {
            system("ls > temp_ls.txt");
            stat("temp_ls.txt", &obj);
            size = obj.st_size;
            send(clnt_sock, &size, sizeof(int), 0);
            filehandle = open("temp_ls.txt", O_RDONLY);
            sendfile(clnt_sock, filehandle, NULL, size);
        } else if (!strcmp(command, "pwd")) {
            system("pwd > temp_pwd.txt");
            i = 0;
            FILE *f = fopen("temp_pwd.txt", "r");
            while (!feof(f))
                buf[i++] = fgetc(f);
            buf[i - 1] = '\0';
            fclose(f);
            send(clnt_sock, buf, 100, 0);
        } else if (!strcmp(command, "cd")) {
            if (chdir(buf + 3) == 0)
                c = 1;
            else
                c = 0;
            send(clnt_sock, &c, sizeof(int), 0);
        } else if (!strcmp(command, "quit")) {
            i = 1;
            send(clnt_sock, &i, sizeof(int), 0);
            exit(0);
        }
    }
    //여기 까지
    close(clnt_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
