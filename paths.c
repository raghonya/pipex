/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:47 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:56:50 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;
	int	j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	j = 0;
	while (envp[i][j] != '/')
		j++;
	return (ft_split(envp[i], ':'));
}
