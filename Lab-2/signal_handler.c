/* Sample program to handle system signals */
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

#include <unistd.h>

void * signal_handler(int signumber)
{
    printf("\nTermination Signal Handled!!\n\n");
    switch(signumber)
    {
        case SIGINT:
            printf("\nSIGINT Signal Handled!!\n\n");
            break;
        case SIGQUIT:
            printf("\nSIGQUIT Signal Handled!!\n\n");
            break;
        case SIGTERM:
            printf("\nSIGTERM Signal Handled!!\n\n");
            break;
        case SIGFPE:
            printf("\nSIGFPE Signal Handled!!\n\n");
            break;
        case SIGSEGV:
            printf("\nSIGSEV Signal Handled!!\n\n");
            break;
        case SIGILL:
            printf("\nSIGILL Signal Handled!!\n\n");
            break;
        default:
            break;
    }
}

int length(int * arr)
{
    return sizeof(arr)/ sizeof(int);
}

int* arr_sigs()
{
    int arr[] = {SIGINT , SIGQUIT, SIGTERM, SIGFPE, SIGSEGV, SIGILL};
    return &arr;
}

int main()
{
    int signals[] = {SIGINT , SIGQUIT, SIGTERM, SIGFPE, SIGSEGV, SIGILL};
    int i = 0;

    pid_t pid = getpid();
    printf("Current Process PID:%d\n", pid);
    // for(i =0 ; i < length(signals); i++ )
    // {
    // signal( signals[i], (void *) signal_handler );
    // }
    signal(signals[0],(void *) signal_handler );
    signal(signals[1],(void *) signal_handler );


    signal(signals[2],(void *) signal_handler );

    signal(signals[3],(void *) signal_handler );
    signal(signals[4],(void *) signal_handler );


    signal(signals[5],(void *) signal_handler );
        while(1) {
            printf("Doing Nothing...\n");
            sleep(1000);
        }
}

