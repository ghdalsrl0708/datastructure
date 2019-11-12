#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PERMS 0644

int main(void) {
	int fd = 0;
	char * pathname = "./mymsg.txt";
	// fd = creat (pathname, PERMS);
	fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, PERMS);
	if (fd == -1) {
		perror("open() error!");
		exit(-1);
	}
	printf("fd of %s is : %d", pathname, fd);

	close(fd);

	return 0;
}
