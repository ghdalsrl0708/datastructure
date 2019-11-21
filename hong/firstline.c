#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main( )
{
	FILE *p_file;
	char str[64];
	
	p_file = fopen("Text.txt", "rt");
	if (p_file != NULL){
		if (fgets(str,64,p_file)!=NULL){
			printf("%s", str);
		}
		else{
			printf("파일에서 문자열을 읽을 수 없습니다.\n");
		}
		fclose(p_file);
	}

	return 0;
}
