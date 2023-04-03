#include <pipex.h>

char	*path_check(char **paths, char *cmd)
{
	char	*tmp;

	if (!cmd)
		return (NULL);
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
	free (cmd);
	return (NULL);
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