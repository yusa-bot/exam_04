#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// Allowed functions: pipe, fork, dup2, execvp, close, exit

// popen():
// 別のプログラムを新しいプロセスとして起動し、
	// そのプロセスとデータをやり取りするための「パイプ（通信路）」を開く関数
	// = 親と子をpipeで繋ぐ (pipe| では、子と子)
// 双方向パイプを作成 -> フォーク -> シェルを起動 -> プロセスを開く
	//  -> 親プロセスのストリームを子プロセスで閉じる

r: outputをつなぐ
w: input

// int execvp(const char *file, char *const argv[]);

int ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	if (pipe(fd) < 0)
		return -1;

	pid = fork();

	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return -1;
	}

	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(1);
		}
		close(fd[0]);
		close(fd[1]);

		execvp(file, argv);

		exit(1);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return(fd[0]);
		}
	}




}

int main()
{
    int  fd;
    char *line;

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((line = get_next_line(fd)))
        ft_putstr(line);
    return (0);
}

int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		printf("%s", line);
}