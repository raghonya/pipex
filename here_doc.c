#include <pipex.h>

// argc = 9, 5 cmd, 5 pipe
// here_doc, LIMITER, -out file, -exec name ==> -4
//ac = 3 in p[0], out p[3]
//ac = 7 in p[8], out b
//ac = 4, 5, 6

void	to_direct_heredoc(t_args arg, int ac, int *p)
{
	int	i;

	i = -1;
	// ac = 3 ... 7
	// pipes: 0 1, 2 3, 4 5, 6 7, 8 9
	if (ac == 3)
	{
		err_pipe(dup2(p[0], STDIN_FILENO) == -1);
		err_pipe(dup2(p[ac], STDOUT_FILENO) == -1);
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
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7]) ([8] [9])
//      rd  wr    rd  wr    rd   wr   rd   wr
// ac = 3, kardum a p[0], talis p[3]
// ac = 4, kardum a p[2], talis p[5]
// ac = 5, kardum a p[4], talis p[7]
// ac = 6, kardum a p[6], talis p[9]
// ac = 7, kardum a p[8], talis fd(b)
// i = (ac - 3) * 2  ==> kardum a p[i], talis p[i + 3]

void	childs_heredoc(t_args arg, char **paths, int ac, int *p)
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
		to_direct_heredoc(arg, ac, p);
		execve(*args, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
		exit (1);
	}
	free_2d(args);
}


void	here_doc(t_args arg, char **paths)
{
	char	*limiter;
	int		*pipefd;
	char	*line;
	int		ac;
	int		i;

	pipefd = malloc(sizeof(int) * (arg.argc - 4) * 2);
	err_pipe(!pipefd);
	i = -1;
	while (++i < arg.argc - 4)
		err_pipe(pipe(pipefd + (i * 2)) == -1);
	limiter = ft_strjoin(arg.argv[2], "\n");
	line = get_next_line(0);
	while (line && ft_strcmp(line, limiter))
	{
		write (pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	ac = 2;
	while (++ac < arg.argc - 1)
		childs_heredoc(arg, paths, ac, pipefd);
	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}

//./pipex here_doc LIMITER cmd cmd1 file

//Should behave like:

//cmd << LIMITER | cmd1 >> file