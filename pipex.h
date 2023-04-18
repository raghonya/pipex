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

typedef struct s_strs
{
	char	*until_dlr;
	char	*tmp;
	char	*to_free;
}	t_strs;

void	free_2d(char **s);

void	to_close(int *pipefd, t_args arg);

void	err_pipe(int a, int *pipes, t_args arg);

char	**paths_finder(char **envp);

char	*path_check(char **paths, char *cmd);

void	find_absolute_path(char **args, char **paths);

void	pipes(t_args arg, char **paths);

void	here_doc(t_args arg, char **paths);

char	*expand(char *line, t_args arg, int *pipes);

char	*strjoin_w_free(char*s1, char *s2);

char	*until_whitespc(char *s);

char	*check_env(char *line, char **env);

#endif
