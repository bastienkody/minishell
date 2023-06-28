#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	char	*str = ft_strdup("salut a tous $USER \"$USER\"");

	if (argc > 1)
	{
		free(str);
		str = ft_strdup(argv[1]);
	}
	ft_fprintf(1, "%i\n", is_there_a_blank(str));
}


// normal dollar expansion
/*int	main(int argc, char **argv, char **envp)
{
	char	*str = ft_strdup("salut a tous $USER \"$USER\"");

	if (argc > 1)
	{
		free(str);
		str = ft_strdup(argv[1]);
	}
	ft_fprintf(1, "%s\n", str);
	str = expand_dollar(str, envp);
	ft_fprintf(1, "%s\n", str);
	free(str);
}*/

// here_doc incl. expansion
/*int	main(int argc, char **argv, char **envp)
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
}*/
