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
	if (argc > 5 && !ft_strcmp(argv[1], "here_doc"))
		here_doc(arg, paths);
	else
		multipipes(arg, paths);
	while (wait(NULL) != -1)
		;
	free_2d(paths);
	return (0);
}
