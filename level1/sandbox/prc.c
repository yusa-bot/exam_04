#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0)
	{
		f();
		exit(0);
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == )
	}

	return 1;
}
