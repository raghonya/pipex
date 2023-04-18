/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 20:12:02 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/18 20:12:03 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	some_tricks(char **line, t_args arg, t_strs *str, int *pipes)
{
	int	dollar_ind;

	dollar_ind = find_dollar(*line);
	str->until_dlr = ft_substr(*line, 0, dollar_ind);
	str->tmp = until_whitespc(*line + dollar_ind + 1);
	err_pipe (!str->tmp || !str->until_dlr, pipes, arg);
	str->ret = strjoin_w_free(str->ret, str->until_dlr);
	err_pipe (!str->ret, pipes, arg);
	str->ret = strjoin_w_free(str->ret, check_env(str->tmp, arg.envp));
	err_pipe (!str->ret, pipes, arg);
	*line += dollar_ind + ft_strlen(str->tmp) + 1;
	free(str->until_dlr);
	free(str->tmp);
	return (find_dollar(*line));
}

char	*expand(char *line, t_args arg, int *pipes)
{
	int		dollar_ind;
	t_strs	str;

	dollar_ind = find_dollar(line);
	if (dollar_ind == -1)
		return (line);
	str.to_free = line;
	str.ret = NULL;
	while (dollar_ind != -1)
		dollar_ind = some_tricks(&line, arg, &str, pipes);
	str.ret = strjoin_w_free(str.ret, line);
	err_pipe (!str.ret, pipes, arg);
	free(str.to_free);
	return (str.ret);
}
