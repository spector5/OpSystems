#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>

char* shm;
int id;

void end ()
{
	// detatch from memory
	if (shmdt(shm) == -1)
	{
		printf("Error with shmdt: %d\n", errno);
		exit(1);
	}
	if (shmctl(id, IPC_RMID, 0) == -1)
	{
		printf("Error with shmctl: %d\n", errno);
		exit(1);
	}
	exit(0);
}

void main (int argc, char* argv[])
{
	char* file = "/tmp";
	int size = 10;
	key_t key;
	char* buf = (char*) malloc(size);

	// get key
	if ((key = ftok(file, 0)) == -1)
	{
		printf("Error with ftok: %d\n", errno);
		exit(1);
	}
	// get shared memory id
	if ((id = shmget(key, size, IPC_CREAT | 0600)) == -1)
	{
		printf("Error with shmget: %d\n", errno);
		exit(1);
	}
	// attach to memory, get memory address
	if ((shm = shmat(id, 0, 0)) == (void*)-1)
	{
		printf("Error with shmat: %d\n", errno);
		exit(1);
	}
	
	// set up struct for signal handling
	struct sigaction act, oact;
	act.sa_handler = end;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, &oact) == -1)
	{
		printf("ERROR\n\n");
		exit(1);
	}

	while(1)
	{
		// get what is in memory
		strcpy(buf, shm);
		printf("Shared: %s\n", buf);

		// set what is in memory
		if (strcmp(buf, "Hi") == 0)
			strcpy(shm, "Bye");
		else
			strcpy(shm, "Hi");
		
		sleep(1);
	}
}
