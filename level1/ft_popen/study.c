exec()関数ファミリー: 指定した新しいプログラムに完全に置き換える
	システムコールであるexecve(2)をベース

extern char **environ;

int execve(const char *pathname, char *const argv[], char *const envp[]);

- List（可変長引数） コマンドライン引数
int execl(const char *pathname, const char *arg, ... /* (char  *) NULL */);

int execlp(const char *file, const char *arg, ... /* (char  *) NULL */);

int execle(const char *pathname, const char *arg, ... /*, (char *) NULL, char *const envp[] */);

- Vector配列
int execv(const char *pathname, char *const argv[]);

int execvp(const char *file, char *const argv[]);

int execvpe(const char *file, char *const argv[], char *const envp[]);