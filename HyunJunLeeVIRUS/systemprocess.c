#include <stdlib.h>
#include <stdio.h>
int main()
{
system("ps -au | awk '{print $2 " " $11}'> index.txt");
system("cat index.txt");
return 0;
}