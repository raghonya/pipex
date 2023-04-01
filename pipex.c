#include <pipex.h>

void	free_2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	malloc_err(int a)
{
	if (a)
		exit(1);
}

int main(int argc, char **argv, char **envp)
{
	int 	pipefd[2];
	int		fd1;
	int		fd2;
	pid_t	cpid;

	if (argc < 5)
		return (0);
	if (access(argv[1], R_OK) == -1 || access(argv[argc - 1], W_OK) == -1)
		exit(0);
	// dup2(fd2, STDOUT_FILENO);
	cmds(argc, argv, envp, &cpid);
	if (cpid != 0)
		wait(NULL);
	// printf ("%s\n%s\n", argv[2], argv[3]);
	// system("leaks pipex");
	return (0);
}