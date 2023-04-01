#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <ft_printf.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_2d
{
	char	**paths;
	char	**args;
}	t_2d;

void	cmds(int argc, char **argv, char **envp, pid_t *cpid);
void	malloc_err(int a);

#endif
