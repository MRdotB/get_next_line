#include "get_next_line.h"

void	ft_readi(int fd)
{
	char *line;
	int r;

	while ((r = get_next_line(fd, &line)) > 0)
	{
		printf("r = %d line : |%s|\n", r, line);
		free(line);
	}
		printf("r = %d line : |%s|\n", r, line);
}

int main(int ac, char **av)
{
	int fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		ft_readi(fd);
	}
	else
		ft_readi(0);
	return (0);
}
