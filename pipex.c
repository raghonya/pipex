#include <pipex.h>

void	free_2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i])
			free(s[i]);
	free(s);
}

void	err_pipe(int a)
{
	if (a)
	{
		perror("Error\n");
		exit(1);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	**paths;
	t_args	arg;
	//int		len;

	arg.argc = argc;
	arg.argv = argv;
	arg.envp = envp;
	if (argc < 5)
		return (0);
	paths = paths_finder(envp);
	err_pipe(!paths || !*paths);
	//len = ft_strlen(argv[1]);
	//if (ft_strlen(argv[1]) < 8)
		//len = 8;
	//if (argc > 5 && !ft_strncmp(argv[1], "here_doc", len))
	//	here_doc(arg, paths);
	//else
		pipes(arg, paths);
	while (wait(NULL) != -1)
		;
	free_2d(paths);
	return (0);
}