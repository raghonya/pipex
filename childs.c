#include <pipex.h>

// void	to_direct(t_args arg, int ac, char *cmd, t_pipes p)
// {
// 	int	cpid2;

// 	if (ac == 2)
// 	{
// 		err_pipe(dup2(open (arg.argv[1], O_RDONLY)\
// 			, STDIN_FILENO) == -1);
// 		dup2(p.pipefd1[1], STDOUT_FILENO);
// 	}
// 	else if (ac == arg.argc - 2)
// 	{
// 		dup2(p.pipefd2[0], STDIN_FILENO);
// 		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT | O_TRUNC \
// 			| O_WRONLY, 0644), STDOUT_FILENO) == -1);
// 	}
// 	else
// 	{
// 		err_pipe(pipe(p.pipefd2));
// 		cpid2 = fork();
// 		if (cpid2 == 0)
// 		{
// 			dup2(p.pipefd1[0], STDIN_FILENO);
// 			dup2(p.pipefd2[1], STDOUT_FILENO);
// 		}

// 		close(p.pipefd2[0]);
// 		close(p.pipefd2[1]);
// 		// dup2(p.pipefd1[0], STDIN_FILENO);
// 		// dup2(p.pipefd2[1], STDOUT_FILENO);
// 	}
// 	close(fd);
// 	close((*pipefd)[0]);
// 	close((*pipefd)[1]);
// }

void	to_direct(t_args arg, int ac, int *p)
{
	int	i;

	i = -1;
	if (ac == 2)
	{
		dup2(open (arg.argv[1], O_RDONLY), STDIN_FILENO);
		dup2(p[ac - 1], STDOUT_FILENO);
	}
	else if (ac == arg.argc - 2)
	{
		dup2(p[ac], STDIN_FILENO);
		dup2(open (arg.argv[arg.argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644), STDOUT_FILENO);
	}
	else
	{
		dup2(p[(ac - 3) * 2], STDIN_FILENO);
		dup2(p[(ac - 3) * 2 + 3], STDOUT_FILENO);
		write (2, "ac = ", 5);
		ft_printf ("%d", ac);
		write (2, "\n", 1);
		write (2, "read end\n", 9);
		ft_printf ("%d", (ac - 3) * 2);
		write (2, "\n", 1);
		write (2, "write end\n", 10);
		ft_printf ("%d", (ac - 3) * 2 + 3);
		write (2, "\n", 1);
	}
	while (++i < (arg.argc - 4) * 2)
		close(p[i]);
	free(p);
}

// ac = 3
// read end
// 0
// write end
// 3
// ac = 4
// read end
// 2
// write end
// 5
// ac = 5
// read end
// 4
// write end
// 7
// ac = 6
// read end
// 6
// write end
// 9

// argc = 8, 5 cmd, 4 pipe
// -in file, -out file, -exec name ==> -3
//ac = 2 in a, out p[1]
//ac = 7 in p[6], out b
//ac = 3, 4, 5, 6
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7])
//      rd  wr    rd  wr    rd   wr   rd   wr
// ac = 3, kardum a p[0], talis p[3]
// ac = 4, kardum a p[2], talis p[5]
// ac = 5, kardum a p[4], talis p[7]
// ac = 6
// i = (ac - 3) * 2  ==> kardum a p[i], talis p[i + 3]

void	childs(t_args arg, char *cmd, int ac, int *p)
{
	char	**args;
	pid_t	cpid;
	int		fd;
	
	args = ft_split(arg.argv[ac], ' ');
	err_pipe(!args);
	cpid = fork();
	err_pipe(cpid == -1);
	if (cpid == 0)
	{
		to_direct(arg, ac, p);
		execve(cmd, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
		exit (1);
	}
	// close(fd);
	free_2d(args);

}

// typedef struct s_pipes
// {
// 	int		pipefd1[2];
// }	t_pipes;

void	pipes(t_args arg, char **paths)
{
	int		*pipefd;
	char	*cmd;
	int		ac;
	int		i;

	ac = 1;
	i = -1;
	pipefd = malloc(sizeof(int) * (arg.argc - 4) * 2);
	err_pipe(!pipefd);
	while (i < arg.argc - 4)
		err_pipe(pipe(pipefd + (++i * 2)) == -1);
	i = 0;
	// while (i < (arg.argc - 4) * 2)
	// 	printf ("%d ", pipefd[i++]);
	while (++ac < arg.argc - 1)
	{
		if (!until_space(arg.argv[ac], &cmd))
			cmd = path_check(paths, cmd);
		childs(arg, cmd, ac, pipefd);
		free(cmd);
	}
	free_2d(paths);
	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}