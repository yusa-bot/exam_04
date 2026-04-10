#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int    picoshell(char **cmds[])
{
	pid_t pid;
	int fd[2];
	int last_fd = -1;

	int i = 0;

	while (cmds[i])
	{
		if (cmds[i+1] && pipe(fd) == -1)
			return 1;

		pid = fork();

		if (pid == -1)
		{
			if (cmds[i+1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return 1;
		}

		if (pid == 0)
		{
			if (last_fd != -1)
			{
				if (dup2(last_fd, STDIN_FILENO) == -1)
					exit(1);
				close(last_fd);
			}

			if (cmds[i+1])
			{
				close(fd[0]);
				if (dup2(fd[1], STDOUT_FILENO) == -1)
					exit(1);
				close(fd[1]);
			}

			execvp(cmds[i][0], cmds[i]);

			exit(1);
		}

		if (last_fd != -1)
			close(last_fd);

		if (cmds[i+1])
		{
			close(fd[1]);
			last_fd = fd[0];
		}

		i++;
	}

	int status;
	int exit_code = 0;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_code = 1;
	}
	// この時点でどの子か１つでもifに入ったら1になる
	return (exit_code);
}





///*
#include <string.h>

static int count_cmds(int argc, char **argv)
{
    int count = 1;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (fprintf(stderr, "Usage: %s cmd1 [args] | cmd2 [args] ...\n", argv[0]), 1);

    int cmd_count = count_cmds(argc, argv);
    char ***cmds = calloc(cmd_count + 1, sizeof(char **));
    if (!cmds)
        return (perror("calloc"), 1);

    int i = 1, j = 0;
    while (i < argc)
    {
        int len = 0;
        while (i + len < argc && strcmp(argv[i + len], "|") != 0)
            len++;

        cmds[j] = calloc(len + 1, sizeof(char *));
        if (!cmds[j])
            return (perror("calloc"), 1);

        for (int k = 0; k < len; k++)
            cmds[j][k] = argv[i + k];
        cmds[j][len] = NULL;

        // j: argv[]全体
        // k: argv1個づつ

        i += len + 1;  // 飛び越える "|"
        j++;
    }
    cmds[cmd_count] = NULL;

    int ret = picoshell(cmds);

    // Limpiar memoria
    for (int i = 0; cmds[i]; i++)
        free(cmds[i]);
    free(cmds);

    return ret;
}
//*/
