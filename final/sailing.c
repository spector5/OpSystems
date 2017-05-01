#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void end ()
{
	exit(0);	
}

void main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("No args\n");
		exit(1);
	}

	struct sigaction act, oact;
	act.sa_handler = end;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGUSR1, &act, &oact) == -1)
	{
		printf("Could not make signal handler\n");
		exit(1);
	}

	while (1)
	{
		printf("%s, I'm sailing! I'm sailing!\n", argv[1]);
		fflush(stdout);
		sleep(1);
	}
}
