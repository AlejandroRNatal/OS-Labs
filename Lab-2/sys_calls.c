// #include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
char cmd[100];

strcpy(cmd,"ls -al");
system(cmd);

return 0;
}


