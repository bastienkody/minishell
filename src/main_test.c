#include "../inc/minishell.h"

// CD builtin (pwd and error seems good but no actual change in terminal, even if chdir directly called)
/*int	main(int argc, char **argv)
{
	char	*path;

	path = "./../";
	if (argc > 1)
		path = argv[1];
	else
	 (void)argv;
	ft_fprintf(1, "%i\n", cd(path));
	pwd();
	//chdir(path);
}*/


// ECHO builtin (ok args et no args, option -n ok, error write (bad fd) echo returns -1)
int	main(void)
{
	char	*args[5];
	int		status;

	//args[0] = NULL;
	args[0] = "-n";
	//args[0] = "salut";
	args[1] = "aluts";
	args[2] = "lutsa";
	args[3] = "utsal";
	args[4] = NULL;
	status = echo(args);	
	//(void)status;
	ft_fprintf(1, "%i\n", status);
}

// PWD builtin (symlink -> returns the dir pointed to by symlink, ok selon discord minishell)
/*int	main(void)
{
	ft_fprintf(1, "%i\n", pwd());
}*/

// EXECUTE
/*int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*cmd_name;
	char	*cmd_args[3];

	if (argc == 2)
	{
		cmd_name = argv[1];
		cmd_args[1] = NULL;
	}
	else if (argc == 3)
	{
		cmd_name = argv[1];
		cmd_args[1] = argv[2];
		cmd_args[2] = NULL;
	}
	else
	{
		cmd_name = "ls";
		cmd_args[1] = "-l";
		cmd_args[2] = NULL;
	}
	cmd_args[0] = cmd_name;
	pid = fork();
	if (pid == 0)
		execute(cmd_name, cmd_args, envp);
	else
	{
		wait(&status);
		ft_fprintf(1, "status : %i\n", status);
		ft_fprintf(1, "analyze(status) : %i\n", analyze_status(status));
	}
	return (analyze_status(status));
}*/

// GET FULL CMD NAME (ok with unset path)
/*int	main(int argc, char **argv, char **envp)
{
	char	*cmd_name;
	char	*full_cmd_name;

	if (argc == 2)
		cmd_name = argv[1];
	else
		cmd_name = "ls";
	full_cmd_name = get_full_cmd_name(cmd_name, envp);
	ft_fprintf(1, "%s\n", full_cmd_name);
	free(full_cmd_name);
}*/

// GET_PATH (ok with unset path)
/*int	main(int argc, char **argv, char **envp)
{
	char	**path;
	char	**path_tmp;

	(void)argc;
	(void)argv;
	
	path = get_path(envp);
	path_tmp = path;
	while(path_tmp && *path_tmp)
		ft_fprintf(1, "%s\n", *path_tmp++);
	free_char_matrix(path);
}*/

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
/*int	main(void)
{
	char	*str = ft_strdup("salut\"\'yo\"");

	str = rm_peer_quotes(str);
	ft_fprintf(1, "%s\n", str);
	free(str);
}*/

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
