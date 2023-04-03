#include <pipex.h>


//void	to_direct_heredoc(t_args arg, int ac, int *(pipefd[2]))
//{
//	if (ac == 3)
//	{

//		dup2((*pipefd)[2], STDIN_FILENO);
		
//		dup2((*pipefd)[1], STDOUT_FILENO);
//	}
//	else if (ac == arg.argc - 2)
//	{
//		dup2((*pipefd)[0], STDIN_FILENO);
//		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT | O_APPEND | O_WRONLY, 0644), STDOUT_FILENO) == -1);
//	}
//	else
//	{
//		dup2((*pipefd)[0], STDIN_FILENO);
//		close ((*pipefd)[0]);
//		close ((*pipefd)[1]);
//		pipe((*pipefd));
//		dup2((*pipefd)[1], STDOUT_FILENO);
//	}
//	close((*pipefd)[0]);
//	close((*pipefd)[1]);
//}

//void	childs_heredoc(t_args arg, char *cmd, int ac, int pipefd[2])
//{
//	char	**args;
//	pid_t	cpid;
	
//	args = ft_split(arg.argv[ac], ' ');
//	err_pipe(!args);
//	cpid = fork();
//	err_pipe(cpid == -1);
//	if (cpid == 0)
//	{
//		to_direct_heredoc(arg, ac, &pipefd);
//		execve(cmd, args, arg.envp);
//		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
//	}
//	free_2d(args);

//}

//void	here_doc(t_args arg, char **paths)
//{
//	int		pipefd[4];
//	char	*limiter;
//	char	*line;
//	char	*cmd;
//	int		out_fd;
//	int ac = 2;

//	pipefd[2] = open("tmpfile.pipex", O_CREAT | O_TRUNC | O_RDWR, 0644);
//	pipe(pipefd);
//	limiter = ft_strjoin(arg.argv[2], "\n");

//	err_pipe(dup2(STDOUT_FILENO, pipefd[3]) == -1);
//	err_pipe(dup2(pipefd[2], STDOUT_FILENO) == -1);
	
//	line = get_next_line(0);
//	while (ft_strncmp(line, limiter, ft_strlen(line)))
//	{
//		ft_printf ("%s", line);
//		free(line);
//		line = get_next_line(0);
//	}

//	err_pipe(dup2(STDOUT_FILENO, pipefd[3]) == -1);
//	while (++ac < arg.argc - 1)
//	{
//		if (!until_space(arg.argv[ac], &cmd))
//			cmd = path_check(paths, cmd);
//		write (pipefd[3], cmd, ft_strlen(cmd));
//		childs_heredoc(arg, cmd, ac, pipefd);
//		free(cmd);
//	}

//	close(pipefd[0]);
//	close(pipefd[1]);
//	close(pipefd[2]);
//	close(pipefd[3]);
//	free(line);
//	free(limiter);
//}

//./pipex here_doc LIMITER cmd cmd1 file

//Should behave like:

//cmd << LIMITER | cmd1 >> file