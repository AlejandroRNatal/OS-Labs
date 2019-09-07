#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN_DELIMETERS " \t\r\n\a"
#define DEFAULT_SIZE 1024

void child_process(int pid, int parent_pid, char* cmd);

char *history[DEFAULT_SIZE];
char *argv[DEFAULT_SIZE];
int hist_count = 0;
int hist_num = 0;
int position = 0;
short isHistNum = 0;

void read_line(char *line){
	if(isHistNum){
		line = memcpy(line,history[hist_num-1],DEFAULT_SIZE);
            	printf("\n");
        }
        else{
            	gets(line);
        }
        isHistNum = 0;
        memcpy(history[hist_count],line,DEFAULT_SIZE);
        hist_count++;
}

void parse_line(char *line,char *argv[]){
	char *token;
	position = 0;
    	token = strtok(line,TOKEN_DELIMETERS);
    	while(token!=NULL){
        	argv[position] = token;
		position++;
        	token =strtok(NULL,TOKEN_DELIMETERS);
    	}
}

int nat_history(char *argv[]){
	if(position==2)
	{
        hist_num = atoi(argv[1]);
		for(int k = 1; k<=hist_count;k++)
		{
			if(hist_num == k)
			{
				isHistNum = 1;
			}
		}
    }		

    if(isHistNum==0)
	{
		for(int i =0; i <hist_count;i++)
				printf(" %d %s\n",(i+1),history[i]);
	}
	return 1;
}

void execute(char *argv[]){
	
	// Check if command is valid as a native command
	char exits[10];	strcpy(exits, "exit");
	char hist[10];	strcpy(hist, "history");
	char help[10]; 	strcpy(help, "help");
	
	if(strcmp(argv[0], exits) == 0){
		exit(0);
	}else if(strcmp(argv[0], hist) == 0){
		nat_history(argv);
	}
	else if(strcmp(argv[0], help) ==0){
		printf("To use this commandline simple type a valid command and hit 'enter'\n");
		printf("help: displays a message explaining how to use the CLI\n");
		printf("exit: closes the CLI\n");
		printf("cd: executes the cd (change directory) command, your shell should manage it natively\nhistory: without parameters, the history command shows a list of all executed commands:\n\n");

	}
		//Native commands
	else
	{	
		//Execute any other command. Uses child process.
		int pid;
		pid = fork();

		if (pid < 0)
		{
			fprintf(stderr, "Fork failed!\n");
			exit(-1);
		}

		else if (pid==0)
		{
			char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
			printf("\n");
			// execv(argv[0], parmList);
			child_process(pid, pid, argv[0]);
			printf("\n\n");
			exit(0);
			printf("Still around...\n\n");
		}

		else 
		{
			//child_process(pid,(int) getpid(), argv[0]);
			int wait_pid = waitpid(pid);

			if( wait_pid < 0)
			{
				// printf("Something went wrong while waiting for child!\n");
				exit(-1);
			}

			else
			{
				// printf("\n\nExecuted Parent successfully\n");
				// printf("Child's PID: %d\n\n", pid);
			// 	char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
			// printf("\n");
			// execv(argv[0], parmList);
			// printf("\n\n");

			}
			//Wait for the child process to finish before continuing
			//exit(0);
		}


	}		
}

char * get_directory_of(char* cmd, char * cdir)
{
	int size = (sizeof(cmd) / sizeof(char));
	cdir = (char *) malloc(size+6 * sizeof(char)) ;// /bin/

	for (int i=0 ; i < size-5 ; i++)
	{
		cdir[i+5] =  cmd[i];
	}
	*cdir = '/';
	*(cdir+1) = 'b';
	*(cdir+2)= 'i';
	*(cdir+3)= 'n';
	*(cdir+4)= '/';

	*(cdir+size-1)= '\0';

	for (int i=0 ; i < size; i++)
	{
		printf("%c",cdir[i]);
	}
	printf("\n");
	return cdir;

}

void child_process(int pid, int parent_pid, char* cmd)
{
	// char * direct_to_exec;
	// get_directory_of(cmd, direct_to_exec);
	// char *const parmList[] = {"/bin/ls", "-l", NULL};
    //printf("Child PID: %d \nParent PID: %d\n\n", pid, parent_pid);
	// execl(direct_to_exec, cmd,(char *) NULL);
	system(cmd);
	exit(0);
}

int main(int argc, char *argv[]){
	int valid = 0;
	char *line = (char*)malloc(DEFAULT_SIZE);

	for(int i = 0;i<DEFAULT_SIZE;i++)
		history[i] = (char*)malloc(DEFAULT_SIZE);

	long size;
	char *buf;
	char *ptr;

	while(1)
	{
		printf("What Will Pika Do?->");
		read_line(line);
		parse_line(line,argv);
		execute(argv);
		for(int j = 0; j< DEFAULT_SIZE;j++){
        		argv[j] = NULL;
		}	
	}

	free(history);
	free(line);
}