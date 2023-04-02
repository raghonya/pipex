#include <pipex.h>

void	to_direct(t_args arg, int ac, int *(pipefd[2]))
{
	if (ac == 2)
	{
		err_pipe(dup2(open (arg.argv[1], O_RDONLY)\
			, STDIN_FILENO) == -1);
		dup2((*pipefd)[1], STDOUT_FILENO);
	}
	else if (ac == arg.argc - 2)
	{
		dup2((*pipefd)[0], STDIN_FILENO);
		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT | O_TRUNC \
			| O_WRONLY, 0644), STDOUT_FILENO) == -1);
	}
	//else
	//{
	//	//printf ("ac == %d\n", ac);
	//	dup2((*pipefd)[0], STDIN_FILENO);
	//	close((*pipefd)[0]);
	//	close((*pipefd)[1]);
	//	pipe((*pipefd));
	//	printf ("fd1 = %d\n", (*pipefd)[1]);
	//	dup2((*pipefd)[1], STDOUT_FILENO);
	//}
	//close((*pipefd)[0]);
	//close((*pipefd)[1]);
}

void	childs(t_args arg, char *cmd, int ac, int pipefd[2])
{
	char	**args;
	pid_t	cpid;
	
	args = ft_split(arg.argv[ac], ' ');
	err_pipe(!args);
	cpid = fork();
	err_pipe(cpid == -1);
	if (cpid == 0)
	{
		to_direct(arg, ac, &pipefd);
		execve(cmd, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
	}
	else
	{
		
	}
	free_2d(args);

}

void	pipes(t_args arg, char **paths)
{
	int		pipefd[2];
	char	*cmd;
	int		ac;

	ac = 1;
	pipe(pipefd);
	while (++ac < arg.argc - 1)
	{
		if (!until_space(arg.argv[ac], &cmd))
			cmd = path_check(paths, cmd);
		childs(arg, cmd, ac, pipefd);
		free(cmd);
	}
	free_2d(paths);
	close(pipefd[0]);
	close(pipefd[1]);
	
}