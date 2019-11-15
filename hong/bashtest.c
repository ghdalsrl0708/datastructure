#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PERMS 0644

int main(void) {
	int ret = system("openssl des3 -in mymsg.txt -out mymsg.txt.des3");
	
}
