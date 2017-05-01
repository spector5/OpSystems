#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void main (int argc, char* argv[])
{
	int pid;
	if ((pid = fork()) == 0)
	{
		if (execl("./sailing", "sailing", "Hola", NULL) == -1)
		{
			printf("could not exec\n");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		sleep(10);
		
		if (kill(pid, SIGUSR1) == -1)
		{
			printf("Could not kill\n");
			exit(1);
		}
		waitpid(pid, NULL, 0);
		exit(0);
	}
	else
	{
		printf("Could not fork\n");
		exit(1);
	}
}
