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
	FILE *p_file;
	char str[64];
	//char str[64];
	
	p_file = fopen("text.txt", "rt");
	if (p_file != NULL){
		if (fgets(str,64,p_file)!=NULL){
			printf("%s\n", str);
		}
		else{
			printf("파일에서 문자열을 읽을 수 없습니다.\n");
		}
		fclose(p_file);
	}

	int i = 0;
	int retval;

	char *s1 = malloc(sizeof(char)*99); // 동적할당을 통해 읽기 전용 메모리인 문자열 포인터를 이어붙임
	strcpy(s1, "openssl enc -base64 -in ");
	// char *s1 = "openssl des3 -in ";
	//char *s2 ;
	//strcpy(s2, str);
	char *s3 = " -out ";
	char *s4 = ".enc";

	strcat(s1,str);
	strcat(s1,s3);
	strcat(s1,str);
	strcat(s1,s4);
	
	printf("%s\n", s1);
	retval = system(s1);
	//printf("Exit Status %d\n", retval);
	free(s1);



	return 0;
}
