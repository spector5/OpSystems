#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

void main (int argc, char* argv[])
{
	int ret;
	int fd;
	int val;
	struct addrinfo hint;
	struct addrinfo* host_ai;
	char* name = "tokenserver";
	char* host = "cs.bridgewater.edu";

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_addrlen = 0;
	hint.ai_next = NULL;
	
	if ((ret = getaddrinfo(host, name, &hint, &host_ai)) != 0)
	{
		printf("Error with get addr: %d\n", ret);
		exit(1);
	}
	if ((fd = socket(host_ai->ai_addr->sa_family, SOCK_STREAM, 0)) < 0)
	{
		printf("Error with socket: %d\n", errno);
		exit(1);	
	}
	if (connect(fd, host_ai->ai_addr, host_ai->ai_addrlen) == -1)
	{
		printf("Error connecting: %d\n", errno);
		exit(1);
	}

	val = recv(fd, &val, sizeof(val), 0);
	printf("Got %d from server", val);
	
	freeaddrinfo(host_ai);
	close(fd);
}
