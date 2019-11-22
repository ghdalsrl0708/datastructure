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
	int line_count =0; //라인수
	char buffer[128]; // 버퍼 파일명을 담을 곳
	FILE *p_file = NULL;
	
	p_file = fopen("temp_ls.txt", "rt"); // 파일명들이 담긴 텍스트 파일을 오픈
	
	if ( p_file != NULL){
		while (fgets(buffer,128, p_file) != NULL){
			line_count++; // 줄단위내용(파일)
			if (buffer[strlen(buffer)-1] == '\n') // 마지막줄은 개행 제거 불필요-> 제외 시킴
			buffer[strlen(buffer)-1] = '\0'; //개행문자 제거 NULL에서의 오류를 \0 을 통해 해결 문수짱의 신의 한수

			int i = 0;
			int retval;

			char *s1 = malloc(sizeof(char)*99); // 동적할당을 통해 읽기 전용 메모리인 문자열 포인터를 이어붙임
			strcpy(s1, "rm ");
			
			strcat(s1,buffer); //문자열 합치기
			

			retval = system(s1); //명령어 이행
	
			free(s1);

		}
		fclose(p_file);

		printf("\n\n");
	}
	return 0; 
}
