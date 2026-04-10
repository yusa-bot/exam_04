#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int    picoshell(char **cmds[])
{
	int fds[2];
	pid_t pid;

	int	i = 0;

	while (cmds[i])
	{
		if (cmds[i+1] && pipe(fd) == -1)
			return 1;

		pid = fork();
		if (pid == -1)
		{
			if (cmds[i+1])
			{
				close(fds[0]);
				close(fd[1]);
			}
			return 1;
		}

		pid = fork();
		if (pid == -1)
			return 1;

		if (pid == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			clode(fds[1]);
			execvp(cmds[i][0], cmds[i]);
		}


		close(fds[0]);
		close(fds[1]);
		i++;
	}

	wait();
	return 0;
}
