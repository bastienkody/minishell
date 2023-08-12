/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:19:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/12 17:12:52 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_parenthesis_closed(t_llist *token_list, char **operator_err)
{
	t_llist	*current;
	t_token	*current_token;
	int n;

	n = 0;
	current = token_list;
	while (current != NULL && n >= 0)
	{
		current_token = current->content;
		if (current_token->type == opening_parenthesis)
			n += 1;
		else if (current_token->type == closing_parenthesis)
			n -= 1;
		current = current->next;
	}
	if (n > 0)
		*operator_err = "(";
	else if (n < 0)
		*operator_err = ")";
	else
		*operator_err = "";
	return (n);
}

int	check_error(t_llist *token_list)
{
	char *operator_err;

	if (llstfind_if(token_list, (t_predicate)is_token_error) != NULL)
		return (ft_fprintf(2, "minishell : token error\n"), -1);
	if (check_parenthesis_closed(token_list, &operator_err) != 0)
		return (print_syntax_error(operator_err), -1);
	if (check_syntax(token_list, &operator_err) != 0)
		return (print_syntax_error(operator_err), -1);
	return (0);
}

// int	set_ast(t_ntree **ast, const char *line, char **envp)
// {
// 	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
// 	token_list = tokenization(line);
// 	if (token_list == NULL)
// 		return (EXIT); // malloc error
// 	token_list = expand_token_list(token_list, envp);
// 	if (token_list == NULL)
// 		return (EXIT); // malloc error
// 	ft_fprintf(1, "DEBUG : TOKEN_LIST\n");
// 	llstiter(token_list, (void *)token_print);
// 	ft_fprintf(1, "\n");
// 	if (check_error(token_list) != 0)
// 		return (CONTINUE); // Token/syntax error
// 	*ast = parser(token_list);
// 	if (*ast == NULL)
// 		return (EXIT); // malloc error
// 	ast_print(*ast);
// 	// manage_here_doc(*ast, envp);
// 	// manage_redir(*ast, envp);
// 	// if (manage_pipeline(*ast, *ast, envp) == 0)
// 	// 	return (EXIT);
// 	return (CONTINUE);
// }

int	interpret_command(const char *line, t_minishell *minishell)
{
	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
	token_list = tokenization(line);
	if (token_list == NULL)
		return (EXIT); // malloc error
	token_list = expand_token_list(token_list, minishell);
	if (token_list == NULL)
		return (EXIT); // malloc error
	if (llstsize(token_list) == 0)
		return (minishell->status = 0, CONTINUE);
	if (check_error(token_list) != 0)
		return (minishell->status = 2, CONTINUE); // Token/syntax error
	minishell->ast = parser(token_list);
	manage_here_doc(minishell->ast, minishell->envp, minishell->status, &minishell->here_doc_files);
	manage_redir(minishell->ast, minishell->envp);
	if (manage_pipeline(minishell, minishell->ast) != 0)
		return (EXIT);
	minishell->status = execute_ast(minishell);
	return (free_loop(minishell), CONTINUE);
}

void	reader_loop(t_minishell *minishell)
{
	int	return_code;

	__attribute__((cleanup(data_cleanup))) char *line;
	line = NULL;
	set_prompt_signals();
	line = readline("minishell prompt % ");
	if (line == NULL)
		return ;
	else if (is_str_blank(line))
		return (reader_loop(minishell));
	add_history(line);
	return_code = interpret_command(line, minishell);
	if (return_code == EXIT)
		return ((void)(minishell->status = 1));
	return (reader_loop(minishell));
}
