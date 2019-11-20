//두번째 방법으로 생각하던 문제였지만 첫번째 방법으로 끝냈습니다.
//컴퓨터내 프로세스를 execv함수를 이용해서 받아옵니다.
//By using execv fuction you can get 'ps -al' results.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const * argv[]) {
pid_t pid = 0;
int status = 0;
char * args[] = {"ps", "-a", "-l", NULL};
pid = fork();
switch (pid) {
case -1:
perror("fork() error!"); exit(-1);
case 0:
execv("/bin/ps", args); break;
}
if (pid > 0) { wait(&status); }

return 0;
}
