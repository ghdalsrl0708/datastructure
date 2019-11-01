#include <fcntl.h> 
#include <pwd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

void myError(const char * msg); 

int main(int argc, char const * argv[]) {
	
	struct stat fileInfo; 
	struct passwd * userInfo;

	if (argc != 2) { 
		printf("Usage: %s [pathname]\n", argv[0]); exit(-1); 
	}
	printf("File name or path: %s\n", argv[1]); 
	if (stat(argv[1], &fileInfo) == -1) {
		myError("stat() error!");
	}
	
	printf("File size: %ld\n", fileInfo.st_size);
	userInfo = getpwuid(fileInfo.st_uid); //stat구조체에서 사용자uid를 가져와서 인자로 넣어 사용자 이름을 알아 냄.

	printf("Owner name: %s\n", userInfo->pw_name);
	return 0;
}

void myError(const char * msg) { 
	perror(msg); exit(-1); 
}