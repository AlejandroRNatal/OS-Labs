
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void child_process(int pid, int parent_pid)
{
    printf("Child PID: %d \nParent PID: %d\n\n", pid, parent_pid);
}


void main()
{
    int pid;
    pid = fork();

    if (pid < 0)
     {
        fprintf(stderr, "Fork failed!\n");
        exit(-1);
    }

    else if (pid==0)
     {
        printf("\n");
        execlp("/bin/ps", "ps", NULL);
        printf("\n\n");

        printf("Still around...\n\n");
    }

    else 
    {
        child_process(pid,(int) getpid());
        int wait_pid = waitpid(pid);

        if( wait_pid < 0)
        {
            printf("Something went wrong while waiting for child!\n");
        }

        else
        {
            printf("\n\nExecuted Parent successfully\n");
            printf("Child's PID: %d\n\n", pid);

        }
        //Wait for the child process to finish before continuing
        exit(0);
    }

}


