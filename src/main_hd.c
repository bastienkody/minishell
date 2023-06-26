#include "../inc/minishell.h"


void	print_env(char **envp)
{
	while (envp && *envp)
	{
		ft_fprintf(1, "%s\n", *envp);
		envp++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	char	*lim;

	if (argc > 1)
		lim = argv[1];
	else
		lim = "eof";

	fd = open_here_doc(lim, envp);
	ft_fprintf(1, "hd fd=%i\n", fd);
	close(fd);
	fd = open_here_doc(lim, envp);
	ft_fprintf(1, "hd fd=%i\n", fd);
	close(fd);
}