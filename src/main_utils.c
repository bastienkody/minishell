/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:57:29 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 10:30:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	set_ast(t_ntree **ast, const char *line, char **envp)
{
	int		return_code;

	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
	token_list = tokenization(line);
	if (token_list == NULL)
		return (EXIT); // malloc error
	return_code = expand_token_list(&token_list, envp);
	if (return_code == 0)
		return (EXIT); // malloc error
	if (return_code == 42)
		return (CONTINUE); // Ambigous redirect
	if (check_error(token_list) != 0)
		return (CONTINUE); // Token/syntax error
	*ast = parser(token_list);
	if (*ast == NULL)
		return (EXIT); // malloc error
	manage_here_doc(*ast, envp);
	manage_redir(*ast, envp);
	if (manage_pipeline(*ast, envp) == 0)
		return (EXIT);
	return (OK);
}

int	interpret_command(const char *line, char ***envp)
{
	int		return_code;

	__attribute__((cleanup(ast_cleanup))) t_ntree * ast;
	ast = NULL;
	return_code = set_ast(&ast, line, *envp);
	if (return_code != OK)
		return (return_code);
	return_code = execute_ast(ast);
	*envp = NULL;
	return (return_code);
}

void	reader_loop(char **envp)
{
	int	return_code;

	__attribute__((cleanup(data_cleanup))) char *line;
	set_prompt_signals();
	line = NULL;
	return_code = read_command(&line);
	if (return_code == EOF)
		return ;
	if (return_code == LINE_EMPTY)
		return (reader_loop(envp));
	add_history(line);
	return_code = interpret_command(line, &envp);
	if (return_code == EXIT)
		return ;
	return (reader_loop(envp));
}
