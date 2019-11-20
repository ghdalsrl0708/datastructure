//pid를 입력 받는데로 계속 kill하는 프로그램입니다.
#include <stdio.h>
#include <signal.h>

int main()
{

pid_t pid;

for(int i=0; i<1000; i++){
scanf("%d",&pid);
kill(pid,SIGKILL);

}
    return 0;
}

//modified as requested 1.get read of extra header files 2. continue kill process when type PID need no limitation
