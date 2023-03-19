#include <pipex.h>

void	args_parse(int argc, char **argv)
{
	int		fd1;
	int		fd2;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_WRONLY);
	err_pipe(fd1 < 0 || fd2 < 0);
	

}