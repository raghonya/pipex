#include <pipex.h>

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

char	*after_eq(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	i++;
	return (s + i);
}

char	*strjoin_w_free(char*s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	int		i;
	int		k;
	char	*s;

	if (!s1)
		return (ft_strdup(s2));
	i = -1;
	k = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (s);
	while (++i < (int)(len1 + len2))
	{
		if (i < (int)len1)
			s[i] = s1[i];
		else
			s[i] = s2[k++];
	}
	s[i] = 0;
	free(s1);
	return (s);
}

char	*until_whitespc(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '$')
		i++;
	ret = malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '$')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*check_env(char *line, char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!*line)
		return ("$");
	while (env[i])
	{
		tmp = until_eq(env[i]);
		if (!ft_strcmp(tmp, line))
		{
			free(tmp);
			return (after_eq(env[i]));
		}
		free(tmp);
		i++;
	}
	return ("");
}
