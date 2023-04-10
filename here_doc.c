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

// typedef struct s_str
// {
// 	char	*until_dlr;
// 	char	*after_spc;
// 	char	*var;
// }	t_str;

// char	*vorevefunc(char **to_wr, char *line, int ind, char **env)
// {
// 	char	*tmp2;
// 	char	*tmp;
// 	t_str	str;
// 	int		i;

// 	str.until_dlr = ft_substr(line, 0, ind);//malloc
// 	str.var = until_whitespc(line);//malloc
// 	str.after_spc = ft_strdup(line + ind + ft_strlen(str.var) + 1);//malloc
// 	err_pipe(!str.until_dlr || !str.var || !str.after_spc);
// 	i = -1;
// 	while (env[++i])
// 	{
// 		tmp = until_eq(env[i]);
// 		err_pipe(!tmp);
// 		if (!ft_strcmp(str.var, tmp))
// 		{
// 			free(tmp);
// 			tmp = ft_strjoin(str.until_dlr, after_eq(env[i]));
// 			tmp2 = tmp;
// 			tmp = ft_strjoin(tmp, str.after_spc);
// 			free(tmp2);
// 			break ;
// 		}
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	if (!tmp)
// 		tmp = ft_strjoin(str.until_dlr, str.after_spc);
// 	free(str.until_dlr);
// 	free(str.var);
// 	free(str.after_spc);
// 	return (tmp);
// }

// void	variables(char **to_wr, char *line, char **env)
// {
// 	char	*tmp2;
// 	char	*tmp;
// 	int		i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		printf ("%c\n", line[i]);
// 		if (line[i] == '$')
// 		{
// 			if (*to_wr)
// 				tmp2 = ft_strdup(*to_wr);
// 			else
// 				tmp2 = ft_strdup(line);
// 			// printf ("to join: %s\n", tmp);
// 			// printf ("arden join arac: %s\n", *to_wr);
// 			tmp = vorevefunc(to_wr, tmp2, i, env);
// 			*to_wr = ft_strjoin(*to_wr, tmp);
// 			free(tmp);
// 		}
// 	}
// 	// printf ("verjnakan: %p\n", *to_wr);
// 	// printf ("tmp2: %p\n", tmp2);
// 	if (!**to_wr)
// 		*to_wr = ft_strdup(line);
// 	free(tmp2);
// }

// char	*after_eq(char *s)
// {
// 	while (*s != '=')
// 		s++;
// 	s++;
// 	return (s);
// }

// char	*until_eq(char *s)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (s[i] != '=')
// 		i++;
// 	ret = malloc(i + 1);
// 	i = 0;
// 	while (*s != '=')
// 		ret[i++] = *s++;
// 	ret[i] = 0;
// 	return (ret);
// }

// char	*until_whitespc(char *s)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	while (*s != '$')
// 		s++;
// 	s++;
// 	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
// 		i++;
// 	ret = malloc(i + 1);
// 	i = 0;
// 	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
// 	{
// 		ret[i] = s[i];
// 		i++;
// 	}
// 	ret[i] = 0;
// 	return (ret);
// }

// argc = 9, 5 cmd, 5 pipe
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7]) ([8] [9])
//      rd  wr    rd  wr    rd   wr   rd   wr   rd   wr
// ac = 3, kardum a p[0], talis p[3]
// ac = 4, kardum a p[2], talis p[5]
// ac = 5, kardum a p[4], talis p[7]
// ac = 6, kardum a p[6], talis p[9]
// ac = 7, kardum a p[8], talis fd(b)
// i = (ac - 3) * 2  ==> kardum a p[i], talis p[i + 3]

void	to_direct_heredoc(t_args arg, int ac, int *p)
{
	int	i;

	i = -1;
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
	while (++i < (arg.argc - 4) * 2)
		close(p[i]);
	free(p);
}

void	childs_heredoc(t_args arg, char **paths, int ac, int *p)
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

void	to_close(int *pipefd, t_args arg)
{
	int	i;

	i = -1;
	while (++i < (arg.argc - 4) * 2)
		close(pipefd[i]);
	free(pipefd);
}

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
