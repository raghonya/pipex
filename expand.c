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

void	create_line(char **line, t_args arg, t_strs *str, int *pipes)
{
	int	dollar_ind;
	int	length;

	dollar_ind = find_dollar(*line);
	while (dollar_ind != -1)
	{
		length = 0;
		str->until_dlr = ft_substr(*line, 0, dollar_ind);
		// printf ("until dollar: %s\n", str->until_dlr);
		str->tmp = until_whitespc(*line + dollar_ind + 1, &length);
		// printf ("tmp: %s\n", str->tmp);
		err_pipe (!str->tmp || !str->until_dlr, pipes, arg);
		str->ret = strjoin_w_free(str->ret, str->until_dlr);
		err_pipe (!str->ret, pipes, arg);
		if (!*str->tmp)
			*line += dollar_ind + length + 1;
		else
			*line += dollar_ind + ft_strlen(str->tmp) + 1;
			// printf ("%d\n,",  length);
		str->ret = strjoin_w_free(str->ret, check_env(str->tmp, arg.envp, length));
		err_pipe (!str->ret, pipes, arg);
		// printf ("ret: %s\n", str->ret);
		free(str->until_dlr);
		free(str->tmp);
		dollar_ind = find_dollar(*line);
	}
	str->ret = strjoin_w_free(str->ret, *line);
	err_pipe (!str->ret, pipes, arg);
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
	create_line(&line, arg, &str, pipes);
	free(str.to_free);
	printf ("ret: %s\n", str.ret);
	return (str.ret);
}
