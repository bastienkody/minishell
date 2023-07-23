#include "../inc/minishell.h"

int	is_token_error(t_llist *llst)
{
	t_token	token = *(t_token *)llst;

	return (token.type == error);
}

void	print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	printf("%s\n", type_to_string(ast->type));
	if (ast->type > 0 && ast->type < 9)
		printf(": %s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast);
}

t_llist	*lexer(const char *line)
{
	t_llist *token_list;

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	// llstiter(token_list, print_item);
	token_list = new_llst_with_compound(token_list);
	if (token_list == NULL)
		return (NULL);
	// ft_fprintf(1, "post compound cmds:\n");
	// llstiter(token_list, print_item);
	// ft_fprintf(1, "_________________________\n");
	llstremove_if(&token_list, (int(*)(void *))is_str_blank, free);
	// llstiter(token_list, print_item);
	token_list = type_token(token_list);
	// llstiter(token_list, (void(*)(void *))print_token);
	return (token_list);
}

t_ast	*parser(t_llist	*token_list)
{
	t_llist	*leaf_list;
	int		flag[256];
	t_ast	*ast;

	leaf_list = token_to_leaf(token_list);
	if (leaf_list == NULL)
		return (NULL);
	ast = create_complete_command(leaf_list);
	if (ast == NULL)
		return (NULL);
	ft_fprintf(1, "-------------------------------\n");
	ft_fprintf(1, "astree :\n");
	for (int i = 0; i < 256; i++)
		flag[i] = 1;
	print_tree(ast, flag, 0, 0);
	return (ast);
}

/////////////////////////////////////////////

// charmatrix buble sort
/*int	main(int argc, char **argv, char **envp)
{
	char	**envp_sorted;

	(void)argc;
	(void)argv;
	envp = charmatrix_dup(envp);
	envp_sorted = charmatrix_buble_sort(envp);
	env(envp_sorted, PREFIX_EXPORT);
	free_char_matrix(envp);
	free_char_matrix(envp_sorted);
}*/


// is_a_builtin (echo ok, cd ok, pwd ok, export/unset ok, env ok) 
/*int	main(int argc, char **argv, char **envp)
{
	char	*args[10];

	(void)argc;
	(void)argv;
	envp = charmatrix_dup(envp);
	args[0] = "env";
	args[1] = "-";
	args[2] = "SHiELL";
	args[1] = NULL;
	ft_fprintf(1, "is_a_builtin:%i\n", is_a_builtin(args));
}*/

// Unset builtin 
/*int	main(int argc, char **argv, char **envp)
{
	char	*args[10];

	(void)argc;
	(void)argv;
	envp = charmatrix_dup(envp);
	if (!envp)
		return (ft_fprintf(2, "charmatrix malloc error?\n"));
	args[0] = "unset";
	args[1] = "SHELL";
	args[2] = "PWO";
	args[3] = "OLDPWD";
	args[4] = NULL;
	ft_fprintf(1, "unset:%i\n", unset(args, &envp));
	env(envp, NULL);
	free_char_matrix(envp);
}*/

// charmatric del one
/*int	main(int argc, char **argv, char **envp)
{

	(void)argc;
	(void)argv;
	envp = charmatrix_dup(envp);
	if (!envp)
		return (ft_fprintf(2, "charmatrix malloc error?\n"));
	envp = charmatrix_del_one(envp, "PWDO");
	if (!envp)
		return (ft_fprintf(2, "charmatrix_del_one malloc error?\n"));
	env(envp, NULL);
	free_char_matrix(envp);
}*/


// Env builtin
/*int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	envp = charmatrix_dup(envp);
	if (!envp)
		return (ft_fprintf(2, "charmatrix malloc error?\n"));
	env(envp, NULL);
	free_char_matrix(envp);
}*/

// Export Builtin
int	main(int argc, char **argv, char **envp)
{
	char	*args[10];

	envp = charmatrix_dup(envp);
	if (!envp)
		return (ft_fprintf(2, "charmatrix malloc error?\n"));
	(void)argc;
	(void)argv;
	args[0] = "export";
	args[1] = "newentry=more";
	//args[1] = NULL;
	args[2] = "truc:=machin";
	args[3] = "otherentry=else";
	args[4] = "-";
	args[5] = "PWD=yop";
	args[6] = "[PWD=bad";
	args[7] = NULL;
	ft_fprintf(1, "export:%i\n", export(args, &envp));
	//export(args, &envp);
	print_env(envp, NULL);
	free_char_matrix(envp);
}

// CD builtin
/*int	main(int argc, char **argv, char **envp)
{
	char	*path;

	envp = charmatrix_dup(envp);
	if (!envp)
		return (ft_fprintf(2, "charmatrix malloc error?\n"));
//	print_env(envp);
	path = "./src/token/";
	if (argc > 1)
		path = argv[1];
	else
		(void)argv;
	print_envar_bad("PWD", envp);
	print_envar_bad("OLDPWD", envp);
	ft_fprintf(1, "cd %s : %i\n", path, cd(path, envp));
	print_envar_bad("PWD", envp);
	print_envar_bad("OLDPWD", envp);
	ft_fprintf(1, "cd %s : %i\n", "../../..", cd("../../..", envp));
	//print_env(envp, NULL);
	free_char_matrix(envp);
}*/

// ECHO builtin (ok args et no args, option -n ok, error write (bad fd) echo returns -1)
/*int	main(void)
{
	char	*args[5];
	int		status;

	//args[0] = NULL;
	args[0] = "echo";
	//args[0] = "salut";
	args[1] = "nen";
	args[2] = "first word";
	args[3] = "second word";
	args[4] = NULL;
	if (check_echo(args))
		ft_fprintf(1, "builtin\n");
	else
	 	return (ft_fprintf(1, "NOT BUILTIN (e or E then?)\n"));
	status = echo(args);
	(void)status;
	//ft_fprintf(1, "%i\n", status);
}*/

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

	status = 0;
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
