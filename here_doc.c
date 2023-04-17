/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:41 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:56:43 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	to_direct_heredoc(t_args arg, int ac, int *p)
{
	if (ac == 3)
	{
		err_pipe(dup2(p[0], STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(p[ac], STDOUT_FILENO) == -1, p, arg);
	}
	else if (ac == arg.argc - 2)
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT \
			| O_APPEND | O_WRONLY, 0644), STDOUT_FILENO) == -1, p, arg);
	}
	else
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(p[(ac - 3) * 2 + 3], STDOUT_FILENO) == -1, p, arg);
	}
	to_close(p, arg);
}

void	childs_heredoc(t_args arg, char **paths, int ac, int *p)
{
	char	**args;
	pid_t	cpid;

	args = ft_split(arg.argv[ac], ' ');
	err_pipe(!args, p, arg);
	find_absolute_path(args, paths);
	cpid = fork();
	err_pipe(cpid == -1, p, arg);
	if (cpid == 0)
	{
		to_direct_heredoc(arg, ac, p);
		execve(*args, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
		exit (1);
	}
	free_2d(args);
}

void	here_doc_norm(t_args arg, int **pipefd, char **limiter)
{
	int	i;

	err_pipe(!*arg.argv[2], NULL, arg);
	*pipefd = malloc(sizeof(int) * (arg.argc - 4) * 2);
	err_pipe(!*pipefd, NULL, arg);
	i = -1;
	while (++i < arg.argc - 4)
		err_pipe(pipe(*pipefd + (i * 2)) == -1, *pipefd, arg);
	*limiter = ft_strjoin(arg.argv[2], "\n");
}

// argc = 9, 5 cmd, 5 pipe
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7]) ([8] [9])
//      rd  wr    rd  wr    rd   wr   rd   wr   rd   wr
// ac = 3, kardum a p[0], talis p[3]
// ac = 4, kardum a p[2], talis p[5]
// ac = 5, kardum a p[4], talis p[7]
// ac = 6, kardum a p[6], talis p[9]
// ac = 7, kardum a p[8], talis fd(b)
// i = (ac - 3) * 2  ==> kardum a p[i], talis p[i + 3]

void	here_doc(t_args arg, char **paths)
{
	char	*limiter;
	int		*pipefd;
	char	*line;
	int		ac;

	here_doc_norm(arg, &pipefd, &limiter);
	line = "";
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
			break ;
		line = expand(line, arg);
		write (pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	ac = 2;
	while (++ac < arg.argc - 1)
		childs_heredoc(arg, paths, ac, pipefd);
	to_close(pipefd, arg);
}

// void	here_doc(t_args arg, char **paths)
// {
// 	char	*limiter;
// 	int		*pipefd;
// 	char	*line;
// 	int		ac;

// 	here_doc_norm(arg, &pipefd, &limiter);
// 	line = "";
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		line = get_next_line(0);
// 		if (!line || !ft_strcmp(line, limiter))
// 			break ;
// 		write (pipefd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	free(line);
// 	free(limiter);
// 	ac = 2;
// 	while (++ac < arg.argc - 1)
// 		childs_heredoc(arg, paths, ac, pipefd);
// 	to_close(pipefd, arg);
// }
