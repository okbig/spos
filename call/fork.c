#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20
#include "defined_function.h"

int main()
{
	char str[20];
	int arr[MAX], *status=NULL;
	pid_t cid;
	
	fflush(stdout);	 //OUtput Stream

	accept_str(str);
	accept_nos(arr);

	cid = fork();

	if( cid == 0 ) //CHILD PROCESS
	{
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
		sleep(15);
		sort_desc(arr);
		cnt_words(str);	
		printf("\n*************Child process terminates ***************\n");			
	}
	else
	{
		cid = wait(status);
		printf("\n\n\t Parent process resumed after the execution of child process with PID %d", cid);
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());

		sort_asc(arr);
		cnt_vowels(str);			
	}//end of if-else

	return 0;	
}//end of main
