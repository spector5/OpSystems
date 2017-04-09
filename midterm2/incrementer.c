#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>

int id;

void release()
{
	// clear semephore
	semctl(id, 0, IPC_RMID);
	exit(0);	
}

void main (int argc, char* argv[])
{
	char* file = "/home/alane";
	key_t key;
	int val;

	// get key
	if ((key = ftok(file, 0)) == -1)
	{
		printf("Error with ftok: %d\n", errno);
		exit(1);
	}
	// get semephore id
	if ((id = semget(key, 1, 0666 | IPC_CREAT)) == -1)
	{
		printf("Error with semget: %d\n", errno);
		exit(1);
	}

	// set up handler
	struct sigaction act, oact;
	act.sa_handler = release;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, &oact) == -1)
	{
		printf("ERROR\n\n");
		exit(1);
	}

	while(1)
	{
		// get semephore value
		if ((val = semctl(id, 0, GETVAL)) == -1)
		{
			printf("Error with getval: %d\n", errno);
			exit(1);
		}
		printf("Sem: %d\n", val);
		struct sembuf op[1];
		op[0].sem_num = 0;
		op[0].sem_op = 1;
		op[0].sem_flg = 0;

		// increment semephore
		if ((val = semop(id, op, 1)) == -1)
		{
			printf("Error with increment: %d\n", errno);
			exit(1);
		}
		sleep(1);
	}
}
