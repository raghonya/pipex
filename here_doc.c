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
	
	if (ac == 3)
	{
		err_pipe(dup2(p[0], STDIN_FILENO) == -1);
		err_pipe(dup2(p[ac], STDOUT_FILENO) == -1);
	}
	else if (ac == arg.argc - 2)
	{
		err_pipe(dup2(p[(ac - 3) * 2], STDIN_FILENO) == -1);
		err_pipe(dup2(open (arg.argv[arg.argc - 1], O_CREAT \
			| O_APPEND | O_WRONLY, 0644), STDOUT_FILENO) == -1);
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
// argc = 9, 5 cmd, 5 pipe
// p = ([0] [1]) ([2] [3]) ([4] [5]) ([6] [7]) ([8] [9])
//      rd  wr    rd  wr    rd   wr   rd   wr   rd   wr
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


//char	*middle_adder(char *dst, char *var, char *src, int index)
//{
//	char	*tmp;
//	char	*tfr;
//	int		j;
//	int		i;
	
//	i = 0;
//	j = 0;
//	tfr = dst;
//	printf ("'%s','%s'\n", dst, src);
//	//printf ("%d + %d\n", ft_strlen(dst), ft_strlen(src));
//	tmp = malloc(ft_strlen(dst) + ft_strlen(src) + 1);
//	while (i < index)
//	{
//		printf ("mti ste\n");
//		tmp[i++] = *dst++;
//	}
//	while (*src)
//		tmp[i++] = *src++;
//	while (*dst)
//		tmp[i++] = *dst++;
	//printf ("%s\n", tmp);

	//i = 0;
	//tmp = ft_strdup(dst + index);
	//dst[index] = 0;
	//dst = ft_strjoin(dst, src);
	//src = dst;
	//dst = ft_strjoin(dst, tmp);
	//free(tmp);
	//free(src);
	//return (dst);
//	tmp[i] = 0;
//	printf ("tmp = %s\n", tmp);
//	free(tfr);
//	return (tmp);
//}

// $PATH ara de asinq $PATH meke $SHLVL

char	*after_eq(char *s)
{
	while (*s != '=')
		s++;
	s++;
	return (s);
}

char	*until_eq(char *s)
{
	char	*ret;
	int		i;
	
	i = 0;
	while (s[i] != '=')
		i++;
	ret = malloc(i + 1);
	i = 0;
	while (*s != '=')
		ret[i++] = *s++;
	ret[i] = 0;
	return (ret);
}

char	*until_whitespc(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (*s != '$')
		s++;
	s++;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	ret = malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*vorevefunc(char **to_wr, char *line, int ind, char **env)
{
	char	*until_dlr;
	char	*after_spc;
	char	*tmp2;
	char	*tmp;
	char	*var;
	int		i;

	until_dlr = ft_substr(line, 0, ind);//malloc
	var = until_whitespc(line);//malloc
	after_spc = ft_strdup(line + ind + ft_strlen(var) + 1);//malloc
	err_pipe(!until_dlr || !var || !after_spc);
	i = -1;
	while (env[++i])
	{
		tmp = until_eq(env[i]);
		err_pipe(!tmp);
		if (!ft_strcmp(var, tmp))
		{
			free(tmp);
			tmp = ft_strjoin(until_dlr, after_eq(env[i]));
			tmp2 = tmp;
			tmp = ft_strjoin(tmp, after_spc);
			free(tmp2);
			break ;
		}
		free(tmp);
		tmp = NULL;
	}
	if (!tmp)
		tmp = ft_strjoin(until_dlr, after_spc);
	free(until_dlr);
	free(var);
	free(after_spc);
	return (tmp);
}

void	variables(char **to_wr, char *line, char **env)
{
	char	*tmp;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			j += ft_strlen(line + i) + 1;
			tmp = vorevefunc(to_wr, line, i, env);
			*to_wr = ft_strjoin(*to_wr, tmp);
			free(tmp);
		}
	}
	if (!**to_wr)
		*to_wr = ft_strdup(line);
}

void	here_doc(t_args arg, char **paths)
{
	char	*to_write;
	char	*limiter;
	int		*pipefd;
	char	*line;
	int		ac;
	int		i;

	err_pipe(!*arg.argv[2]);
	pipefd = malloc(sizeof(int) * (arg.argc - 4) * 2);
	err_pipe(!pipefd);
	i = -1;
	while (++i < arg.argc - 4)
		err_pipe(pipe(pipefd + (i * 2)) == -1);
	limiter = ft_strjoin(arg.argv[2], "\n");
	line = "";
	while (1)
	{
		write(1, "heredoc> ", 9);
		to_write = "";
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			break ;
		}
		variables(&to_write, line, arg.envp);
		write (pipefd[1], to_write, ft_strlen(to_write));
		free(line);
		free(to_write);
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