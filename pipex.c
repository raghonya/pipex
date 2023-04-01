#include <pipex.h>

void	free_2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	err_pipe(int a)
{
	if (a)
	{
		perror("");
		exit(1);
	}
}


int main(int argc, char **argv, char **envp)
{
	pid_t	cpid;

	if (argc < 5)
		return (0);
	cmds(argc, argv, envp, &cpid);
	//if (cpid != 0)
	while (wait(NULL) != -1)
		;
	return (0);
}