/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:58 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:57:01 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <ft_printf.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_args
{
	int		fdin;
	int		fdout;
	int		argc;
	char	**argv;
	char	**envp;
}	t_args;

void	pipes(t_args arg, char **paths);
void	err_pipe(int a, int *pipes, t_args arg);
void	free_2d(char **s);
char	*path_check(char **paths, char *cmd);
char	**paths_finder(char **envp);
void	find_absolute_path(char *arg, char **paths);
void	here_doc(t_args arg, char **paths);

#endif
