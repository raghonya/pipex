/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raghonya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:56:23 by raghonya          #+#    #+#             */
/*   Updated: 2023/04/10 16:56:25 by raghonya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i])
			free(s[i]);
	free(s);
}

void	err_pipe(int a, int *pipes, t_args arg)
{
	int	i;

	i = -1;
	if (a)
	{
		if (pipes)
			while (++i < (arg.argc - 4) * 2)
				close(pipes[i]);
		perror("Error");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	t_args	arg;

	arg.argc = argc;
	arg.argv = argv;
	arg.envp = envp;
	if (argc < 5)
		return (0);
	paths = paths_finder(envp);
	err_pipe(!paths || !*paths, NULL, arg);
	if (ft_strlen(argv[1]) == 8 && argc > 5 \
		&& !ft_strncmp(argv[1], "here_doc", 8))
		here_doc(arg, paths);
	else
	{
		arg.fdin = open (arg.argv[1], O_RDONLY);
		arg.fdout = open (arg.argv[arg.argc - 1], O_CREAT \
			| O_TRUNC | O_WRONLY, 0644);
		pipes(arg, paths);
	}
	while (wait(NULL) != -1)
		;
	free_2d(paths);
	return (0);
}
