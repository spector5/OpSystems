#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// global variable
int num;

// will be run by first thread
void* t1 (void* arg)
{
	while (1)
	{
		// check if even
		if (num % 2 == 0)
		{
			printf("EVEN\n");
			fflush(stdout);
			sleep(2);
		}
	}
}

// will be run by second thread
void* t2 (void* arg)
{
	while (1)
	{
		// check if odd
		if (num % 2 != 0)
		{
			printf("ODD\n");
			fflush(stdout);
			sleep(2);
		}
	}
}

// main thread
void main (int argc, char* argv[])
{
	num = 0;
	int i = 1;
	pthread_t tid;	// blank struct to be used to create thread

	srand(time(NULL));	// set up random limit
	int r = rand();		// get random value

	// create two threads with null arguments
	pthread_create(&tid, NULL, t1, NULL);
	pthread_create(&tid, NULL, t2, NULL);
	while (1)
	{
		num = r;
		r = rand();	// get random value
		sleep(1);
	}
}
