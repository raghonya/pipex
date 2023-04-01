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
	cmds(argc, argv, envp, &cpid);
	if (cpid != 0)
		wait(NULL);
	return (0);
}