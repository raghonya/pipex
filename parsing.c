#include <pipex.h>

int	until_space(char *s, char **new)
{
	int	i;
	int	k;

	i = 0;
	while (s[i] != ' ')
		i++;
	*new = malloc(i + 2);
	malloc_err(!*new);
	(*new)[0] = '/';
	i = 0;
	k = 1;
	while (s[i] != ' ')
		(*new)[k++] = s[i++];
	(*new)[k] = 0;
	return (i + 1);
}

char	*path_check(char **paths, char *cmd)
{
	char	*tmp;
	int		i;

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
	int		i;
	int		fd1;
	int		fd2;

	ac = 1;
	arrs.paths = paths_finder(envp);
	malloc_err(!arrs.paths);
	pipe(pipefd);
	while (++ac < argc - 1)
	{
		i = until_space(argv[ac], &cmd);
		arrs.args = ft_split(argv[ac], ' ');
		malloc_err(!arrs.args);
		cmd = path_check(arrs.paths, cmd);
		i = -1;
		*cpid = fork();
		if (*cpid == -1)
			exit (0);
		if (*cpid == 0)
		{
			if (ac == 2)
			{
				fd1 = open (argv[1], O_RDONLY);
				malloc_err(fd1 == -1);
				dup2(fd1, STDIN_FILENO);
				dup2(pipefd[1], STDOUT_FILENO);
			}
			else if (ac == argc - 2)
			{
				fd2 = open (argv[argc - 1], O_WRONLY);
				malloc_err(fd2 == -1);
				dup2(pipefd[0], STDIN_FILENO);
				dup2(fd2, STDOUT_FILENO);
			}
			dup2(pipefd[1], STDIN_FILENO);
			dup2(pipefd[0], STDOUT_FILENO);
			// dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			close(fd1);
			close(fd2);
			i = execve(cmd, arrs.args, envp);
			printf ("execve ret: %d\n", i);
			perror("Command not found\n");
			exit (0);
		}
		i = -1;
		while (arrs.args[++i])
			free(arrs.args[i]);
		free(arrs.args);
		free(cmd);
	}
	while (arrs.paths[++i])
		free(arrs.paths[i]);
	free(arrs.paths);
	
}