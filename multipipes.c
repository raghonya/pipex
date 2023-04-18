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
	close(arg.fdin);
	close(arg.fdout);
	to_close(p, arg);
}

/*

	argc = 8, 5 cmd, 4 pipe
	p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7])
		 rd   wr   rd   wr   rd   wr   rd   wr 
	ac = 2, kardum a fd(a), talis p[1]
	ac = 3, kardum a p[0] , talis p[3]
	ac = 4, kardum a p[2] , talis p[5]
	ac = 5, kardum a p[4] , talis p[7]
	ac = 7, kardum a p[6] , talis fd(b)

	ac = 2, kardum a fd(a), talis p[ac - 1]
	ac = [3...argc - 2], i = (ac - 3) * 2  ==>
	==> kardum a p[i], talis p[i + 3]

*/

void	childs(t_args arg, char **paths, int ac, int *p)
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
		to_direct(arg, ac, p);
		execve(*args, args, arg.envp);
		ft_putstr_fd ("Command not found\n", STDERR_FILENO);
		exit (1);
	}
	free_2d(args);
}

void	multipipes(t_args arg, char **paths)
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
	close(arg.fdin);
	close(arg.fdout);
	free(pipefd);
}
