/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:36 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:56:37 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	to_direct(t_args arg, int ac, int *p)
{
	int	i;

	i = -1;
	if (ac == 2)
	{
		err_pipe(dup2(arg.fdin, STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(p[ac - 1], STDOUT_FILENO) == -1, p, arg);
	}
	else if (ac == arg.argc - 2)
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(arg.fdout, STDOUT_FILENO) == -1, p, arg);
	}
	else
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1, p, arg);
		err_pipe(dup2(p[(ac - 3) * 2 + 3], STDOUT_FILENO) == -1, p, arg);
	}
	while (++i < (arg.argc - 4) * 2)
		close(p[i]);
	free(p);
}

void	childs(t_args arg, char **paths, int ac, int *p)
{
	char	**args;
	char	*tmp;
	pid_t	cpid;

	args = ft_split(arg.argv[ac], ' ');
	err_pipe(!args, p, arg);
	if (*args && **args != '/')
	{
		tmp = ft_strjoin("/", *args);
		free(*args);
		*args = path_check(paths, tmp);
	}
	cpid = fork();
	err_pipe(cpid == -1, p, arg);
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
	err_pipe(!pipefd, NULL, arg);
	i = -1;
	while (++i < arg.argc - 4)
		err_pipe(pipe(pipefd + (i * 2)) == -1, pipefd, arg);
	while (++ac < arg.argc - 1)
		childs(arg, paths, ac, pipefd);
	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}
