#include <pipex.h>

int	find_dollar(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*expand(char *line, t_args arg)
{
	int		dollar_ind;
	char	*ret;
	t_strs	str;

	dollar_ind = find_dollar(line);
	if (dollar_ind == -1)
		return (line);
	str.to_free = line;
	ret = NULL;
	while (dollar_ind != -1)
	{
		str.until_dlr = ft_substr(line, 0, dollar_ind);
		str.tmp = until_whitespc(line + dollar_ind + 1);
		ret = strjoin_w_free(ret, str.until_dlr);
		ret = strjoin_w_free(ret, check_env(str.tmp, arg.envp));
		line += dollar_ind + ft_strlen(str.tmp) + 1;
		free(str.until_dlr);
		free(str.tmp);
		dollar_ind = find_dollar(line);
	}
	ret = strjoin_w_free(ret, line);
	free(str.to_free);
	return (ret);
}