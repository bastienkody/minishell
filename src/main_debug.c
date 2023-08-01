/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 14:26:37 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_token_error(t_llist *llst)
{
	const t_token	token = *(t_token *)llst;

	return (token.type == error);
}

// int	main(int argc, __attribute__((unused))char **argv, char **envp)
// {
// 	char	*line;
// 	t_llist	*token_list;
// 	t_llist	*error;
// 	t_ntree	*ast;
// 	int		last_status;
// 	int		return_code;

// 	if (!argc || !envp)
// 		return (1);
// 	last_status = 0;
// 	while (TRUE)
// 	{
// 		line = NULL;
// 		return_code = read_command(&line);
// 		if (return_code == EOF)
// 			break ;
// 		if (return_code == LINE_EMPTY)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		(token_list = tokenization(line), free(line));
// 		// ft_putendl_fd("-----------TOKEN LIST-----------", 1);
// 		// llstiter(token_list, (void (*)(void *))print_token);
// 		// ft_putendl_fd("", 1);
// 		return_code = expand_token_list(&token_list, envp, last_status);
// 		if (return_code == 0)
// 			exit(1);
// 		if (return_code == 42)
// 		{
// 			llstclear(&token_list, free_token);
// 			ft_fprintf(1, "%s\n", ERR_AMB_REDIR);
// 			continue ;
// 		}
// 		// ft_putendl_fd("-------TOKEN LIST EXPAND-------", 1);
// 		// llstiter(token_list, (void (*)(void *))print_token);
// 		// ft_putendl_fd("", 1);
// 		if (check_syntax != 0)
// 			continue ;
// 		(ast = parser(token_list), llstclear(&token_list, free_token));
// 		if (ast == NULL)
// 			break ; // erreur de malloc
// 		manage_here_doc(ast, envp, last_status);
// 		manage_redir(ast, envp, last_status);
// 		manage_pipeline(ast, envp);
// 		// ft_putendl_fd("-----------AST-----------", 1);
// 		// ast_print(ast);
// 		// ft_putendl_fd("", 1);
// 		last_status = execute_ast(ast);
// 		ast_free(ast);
// 	}
// 	return (0);
// }

void	data_cleanup(char **data)
{
	free(*data);
}

void	token_list_cleanup(t_llist **token_list)
{
	llstclear(token_list, free_token);
}

void	ast_cleanup(t_ntree **ast)
{
	ast_free(*ast);
}

void	do_redirections(t_ntree *ast, char **envp, int last_status)
{
	manage_here_doc(ast, envp, last_status);
	manage_redir(ast, envp, last_status);
}

int	read_command(char **line)
{
	*line = readline("minishell prompt % ");
	if (*line == NULL)
		return (EOF);
	if (is_str_blank(*line))
		return (LINE_EMPTY);
	return (0);
}

int	check_error(t_llist *token_list)
{
	if (llstfind_if(token_list, (t_predicate)is_token_error) != NULL)
		return (-1);
	if (!check_syntax(token_list))
		return (-1);
	return (0);
}

# define CONTINUE 1000
# define EXIT 1001
# define OK 1002

int	set_ast(t_ntree **ast, const char *line, char **envp, int last_status)
{
	int		return_code;

	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
	token_list = tokenization(line);
	if (token_list == NULL)
		return (EXIT); // malloc error
	return_code = expand_token_list(&token_list, envp, last_status);
	if (return_code == 0)
		return (EXIT); // malloc error
	if (return_code == 42)
		return (CONTINUE); // Ambigous redirect
	if (check_error(token_list) != 0)
		return (CONTINUE); // Token/syntax error
	*ast = parser(token_list);
	if (*ast == NULL)
		return (EXIT); // malloc error
	do_redirections(*ast, envp, last_status);
	if (manage_pipeline(*ast, envp) == 0)
		return (EXIT);
	return (OK);
}

int	interpret_command(const char *line, char **envp, int last_status)
{
	int		return_code;

	__attribute__((cleanup(ast_cleanup))) t_ntree * ast;
	ast = NULL;
	return_code = set_ast(&ast, line, envp, last_status);
	if (return_code != OK)
		return (return_code);
	return (execute_ast(ast));
}

// void	reader_loop(char **envp)
// {
// 	int		last_status;
// 	int		return_code;
// 	char	*line;

// 	line = NULL;
// 	last_status = 0;
// 	while (1)
// 	{
// 		return_code = read_command(&line);
// 		if (return_code != 0)
// 		{
// 			free(line);
// 			if (return_code == EOF)
// 				break ;
// 			if (return_code == LINE_EMPTY)
// 				continue ;
// 		}
// 		add_history(line);
// 		return_code = interpret_command(line, envp, last_status);
// 		free(line);
// 		if (return_code == EXIT)
// 			break ;
// 		if (return_code == CONTINUE)
// 			continue ;
// 	}
// }

void	reader_loop(char **envp, int last_status)
{
	int return_code;
	__attribute__((cleanup(data_cleanup))) char	*line;

	line = NULL;
	return_code = read_command(&line);
	if (return_code == EOF)
		return ;
	if (return_code == LINE_EMPTY)
		return (reader_loop(envp, last_status));
	add_history(line);
	return_code = interpret_command(line, envp, last_status);
	if (return_code == EXIT)
		return ;
	return (reader_loop(envp, last_status));
}

int	main(int argc, char **argv, char **envp)
{
	((void)argc, (void)argv);
	reader_loop(envp, 0);
	return (0);
}
