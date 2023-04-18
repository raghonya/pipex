/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:16 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/18 20:12:17 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	to_close(int *pipefd, t_args arg)
{
	int	i;

	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}

void	free_2d(char **s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	err_pipe(int a, int *pipes, t_args arg)
{
	int	i;

	i = -1;
	if (a)
	{
		if (pipes)
			while (++i < (arg.argc - 4) * 2)
				close(pipes[i]);
		perror("Error");
		exit(1);
	}
}
