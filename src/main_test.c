#include "../inc/minishell.h"




//	OPENING FILES
/*int	main(int argc, char **argv, char **envp)
{
	int		in_fd = -7;
	char	*infile;
	int		out_fd = -7;
	char	*outfile;
	char	*str;

	infile = ft_strdup("Makefile");
	outfile = ft_strdup("$truc");
 
	in_fd = open_in(infile, envp);
	out_fd = open_out(5, outfile, envp);
	ft_fprintf(1, "in_fd = %i\n", in_fd);
	ft_fprintf(1, "out_fd = %i\n", out_fd);
	while (in_fd > 0 && out_fd > 0)
	{
		str = get_next_line(in_fd);
		if (!str || !*str)
		{
			free(str);
			break ;
		}
		write(out_fd, str, ft_strlen(str));
		free(str);
	}
	close(in_fd);
	close(out_fd);
}*/

//	QUOTE REMOVAL
int	main(void)
{
	char	*str = ft_strdup("salut\"\'yo\"");

	str = rm_peer_quotes(str);
	ft_fprintf(1, "%s\n", str);
	free(str);
}

// REDIR FILE EXPANSION
/*int	main(int argc, char **argv, char **envp)
{
	char	*str = ft_strdup("\'\"$truc\"\'");
	char	*ret;

	if (argc > 1)
	{
		free(str);
		str = ft_strdup(argv[1]);
	}
	if (check_amb_redir(str, envp))

		ft_fprintf(1, "ok :");
	else
		ft_fprintf(1, "KO :");
	ret = expand_dollar(str, envp);
	ft_fprintf(1, "%s\n", ret);
	free(ret);
}*/

//	DOLLAR EXPANSION
/*int	main(int argc, char **argv, char **envp)
{
	char	*str = ft_strdup("salut \"\'$USER\'\" \'$USER\'");

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

//	HEREDOC N EXPANSION
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
