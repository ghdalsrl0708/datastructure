#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void myError(const char *msg);
void fileMode(const struct stat *fileInfo);

int main(int argc, char const *argv[]) {

    struct stat fileInfo;
    struct passwd *userInfo;

    if (argc != 2) {
        printf("Usage: %s [pathname]\n", argv[0]);
        exit(-1);
    }

    printf("File name or path: %s\n", argv[1]);
    if (stat(argv[1], &fileInfo) == 1) {
        myError("stat() error!");
    }

    printf("File size: %ld\n", fileInfo.st_size);
    printf("File permission: ");
    fileMode(&fileInfo);

    userInfo =
        getpwuid(fileInfo.st_uid); // stat구조체에서 사용자uid를 가져와서 인자로
                                   // 넣어서 사용자의 이름을 알아냄
    printf("Owner name: %s\n", userInfo->pw_name);

    return 0;
}

void myError(const char *msg) {
    perror(msg);
    exit(-1);
}

void fileMode(const struct stat *fileInfo) {

    // User
    if (S_IRUSR & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWUSR & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXUSR & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    // Group
    if (S_IRGRP & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWGRP & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXGRP & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    // Others
    if (S_IROTH & fileInfo->st_mode) {
        printf("r");
    } else {
        printf("-");
    }

    if (S_IWOTH & fileInfo->st_mode) {
        printf("w");
    } else {
        printf("-");
    }

    if (S_IXOTH & fileInfo->st_mode) {
        printf("x");
    } else {
        printf("-");
    }

    puts("");
}
