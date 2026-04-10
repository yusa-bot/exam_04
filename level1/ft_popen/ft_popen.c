
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


//pipe give fd[0](read), fd[1](write)
// if pid == 0 then child process otherwise parent

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pid_t pid;

    if(!file || !argv || (type != 'r' && type != 'w'))
        return(-1);

    if(pipe(fd)== -1)
        return(-1);

    pid = fork();

    if(pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return(-1);
    }

    if(pid == 0)
    {
        if(type == 'r')
        {
            if(dup2(fd[1], STDOUT_FILENO) == -1)
                exit(1);
        }
        else // w
        {
            if(dup2(fd[0], STDIN_FILENO) == -1)
                exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        execvp(file, argv);
        exit(1);
    }
    else
    {
        if(type == 'r')
        {
            close(fd[1]);
            return(fd[0]); // 子がfd[1]をつなげたので、親はそれを読み取るfd[0]を返す
        }
        else
        {
            close(fd[0]);
            return(fd[1]);
        }
    }
}

// 親が返すのは指示通りで、子がdupするのは親が返す逆