#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <ft_printf.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_2d
{
	char	**paths;
	char	**args;
}	t_2d;

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
}	t_args;

void	pipes(t_args arg, char **paths);
void	err_pipe(int a);
void	free_2d(char **s);
char	*path_check(char **paths, char *cmd);
char	**paths_finder(char **envp);
void	here_doc(t_args arg, char **paths);

#endif
