#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void* signal_handler(int sig)
{

    switch(sig)
    {
        case SIGFPE:
            printf("SIGFPE error handled");
            exit(1);
            break;
        case SIGSEGV:
            printf("SIGSEGV error handled");
            exit(1);
            break;
        default:
            exit(1);
            break;
    }
}


int fpe_error()
{
    int arr[4] = {0,1,2,3};

    return arr[1]/arr[0];
}

void printarr(char *arr, int len)
{
    for(int i=0; i <= len; i++)
    {
        printf("%s", arr[i]);
    }

    printf("\n");
}

int main()
{
    void* handlers[2] = {(void  *)signal_handler, (void  *)signal_handler };

    signal(SIGFPE, handlers[0]);
    signal(SIGSEGV, handlers[1]);

    //fpe_error();
    char arr [4] = {'a', 'b', 'c','\0'};
    // int arr[2] = {1,2};
    printarr(arr, 3);
}