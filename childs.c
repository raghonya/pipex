#include <pipex.h>

// void	to_direct(t_args arg, int ac, char *cmd, t_pipes p)
// {
// 	int	cpid2;

// 	if (ac == 2)
// 	{
// 		err_pipe(dup2(open (arg.argv[1], O_RDONLY), STDIN_FILENO) == -1);
// 		dup2(p.pipefd1[1], STDOUT_FILENO);
// 	}
// 	else if (ac == arg.argc - 2)
// 	{
// 		dup2(p.pipefd2[0], STDIN_FILENO);
// 		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644), STDOUT_FILENO) == -1);
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
		err_pipe(dup2(open (arg.argv[1], O_RDONLY), STDIN_FILENO) == -1);
		err_pipe(dup2(p[ac - 1], STDOUT_FILENO) == -1);
	}
	else if (ac == arg.argc - 2)
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1);
		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT \
			| O_TRUNC | O_WRONLY, 0644), STDOUT_FILENO) == -1);
	}
	else
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1);
		err_pipe(dup2(p[(ac - 3) * 2 + 3], STDOUT_FILENO) == -1);
	}
	while (++i < (arg.argc - 4) * 2)
		close(p[i]);
	free(p);
}

// argc = 8, 5 cmd, 4 pipe
// -in file, -out file, -exec name ==> -3
//ac = 2 in a, out p[1]
//ac = 7 in p[6], out b
//ac = 3, 4, 5, 6
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7])
//      rd  wr    rd  wr    rd   wr   rd   wr
// ac = 2, kardum a fd(a), talis p[1]
// ac = 3, kardum a p[0], talis p[3]
// ac = 4, kardum a p[2], talis p[5]
// ac = 5, kardum a p[4], talis p[7]
// ac = 6, kardum a p[6], talis fd(b)
// i = (ac - 3) * 2  ==> kardum a p[i], talis p[i + 3]

void	childs(t_args arg, char **paths, int ac, int *p)
{
	char	**args;
	char	*tmp;
	pid_t	cpid;
	
	args = ft_split(arg.argv[ac], ' ');
	err_pipe(!args);
	if (*args && **args != '/')
	{
		tmp = ft_strjoin("/", *args);
		free(*args);
		*args = path_check(paths, tmp);
	}
	cpid = fork();
	err_pipe(cpid == -1);
	if (cpid == 0)
	{
		to_direct(arg, ac, p);
		execve(*args, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
		exit (1);
	}
	free_2d(args);
}

void	pipes(t_args arg, char **paths)
{
	int		*pipefd;
	int		ac;
	int		i;

	ac = 1;
	pipefd = malloc(sizeof(int) * (arg.argc - 4) * 2);
	err_pipe(!pipefd);
	i = -1;
	while (++i < arg.argc - 4)
		err_pipe(pipe(pipefd + (i * 2)) == -1);
	while (++ac < arg.argc - 1)
		childs(arg, paths, ac, pipefd);
	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}