#include <pipex.h>

void	filler(char *s, char **new)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (s[0] == '/')
		while (s[i] && s[i] != ' ')
			(*new)[k++] = s[i++];
	else
	{
		(*new)[k++] = '/';
		while (s[i] && s[i] != ' ')
			(*new)[k++] = s[i++];
		i = i + 1;
	}
	(*new)[i] = 0;
}

int	until_space(char *s, char **new)
{
	int	i;

	i = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
		i++;
	*new = malloc(i + 2);
	err_pipe(!*new);
	filler(s, new);
	if (s[0] == '/')
		return (1);
	return (0);
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
	free (cmd);
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