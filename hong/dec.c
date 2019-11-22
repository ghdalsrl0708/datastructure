#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char **argv)
{
	char buffer[128];
	int retval;

	printf("복호화를 진행할 파일명(암호화가 진행된 .enc 제외): ");
	scanf("%s", buffer);	

	char *s1 = malloc(sizeof(char)*99); // 동적할당을 통해 읽기 전용 메모리인 문자열 포인터를 이어붙임
	strcpy(s1, "openssl enc -base64 -d -in ");
			
	char *s3 = ".enc -out ";
	char *s4 = ".dec";

	strcat(s1,buffer);
	strcat(s1,s3);
	strcat(s1,buffer);
	strcat(s1,s4);

	retval = system(s1);
	
	free(s1);

	return 0; 
}
