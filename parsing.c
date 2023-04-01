#include <pipex.h>

void	until_space(char *s, char **new)
{
	int	i;
	int	k;

	i = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
		i++;
	*new = malloc(i + 2);
	err_pipe(!*new);
	(*new)[0] = '/';
	i = 0;
	k = 1;
	while (s[i] != ' ')
		(*new)[k++] = s[i++];
	(*new)[k] = 0;
}

char	*path_check(char **paths, char *cmd)
{
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, cmd);
		if (!access (tmp, X_OK))
		{
			free(cmd);
			return (tmp);
		}
		free(tmp);
		paths++;
	}
	return  (NULL);
}

char	**paths_finder(char **envp)
{
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (NULL);
	while (**envp != '/')
		(*envp)++;
	return (ft_split(*envp, ':'));
}

void	cmds(int argc, char **argv, char **envp, pid_t *cpid)
{
	int		pipefd[2];
	t_2d	arrs;
	char	*cmd;
	int		ac;

	ac = 1;
	arrs.paths = paths_finder(envp);
	err_pipe(!arrs.paths);
	pipe(pipefd);
	while (++ac < argc - 1)
	{
		until_space(argv[ac], &cmd);
		arrs.args = ft_split(argv[ac], ' ');
		err_pipe(!arrs.args);
		cmd = path_check(arrs.paths, cmd);
		*cpid = fork();
		if (*cpid == -1)
			exit (0);
		if (*cpid == 0)
		{
			if (ac == 2)
			{
				err_pipe(dup2(open (argv[1], O_RDONLY)\
					, STDIN_FILENO) == -1);
				dup2(pipefd[1], STDOUT_FILENO);
			}
			else if (ac == argc - 2)
			{
				dup2(pipefd[0], STDIN_FILENO);
				err_pipe(dup2(open (argv[argc - 1], O_CREAT | O_TRUNC \
					| O_WRONLY, 0644), STDOUT_FILENO) == -1);
			}
			else
			{
				dup2(pipefd[0], STDIN_FILENO);
				pipe(pipefd);
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			execve(cmd, arrs.args, envp);
			perror("Command not found\n");
			exit (0);
		}
		free_2d(arrs.args);
		free(cmd);
	}
	free_2d(arrs.paths);
	close(pipefd[0]);
	close(pipefd[1]);
	
}