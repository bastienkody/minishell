/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:19:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 16:53:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_parenthesis_closed(t_llist *token_list, char **operator_err)
{
	t_llist	*current;
	t_token	*current_token;
	int		n;

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

t_state	manage_redirection(t_minishell *minishell)
{
	int	return_code;

	return_code = manage_here_doc(minishell->ast, minishell);
	if (return_code == EXIT)
		return (minishell->status = 1, EXIT);
	if (return_code == CONTINUE)
		return (minishell->status = 130, CONTINUE);
	manage_redir(minishell->ast, minishell->envp);
	return (OK);
}

t_state	interpret_command(const char *line, t_minishell *minishell)
{
	int		return_code;
	t_llist	*token_list;

	token_list = tokenization(line);
	if (token_list == NULL)
		return (EXIT);
	if (!check_quotes(token_list))
		return (minishell->status = 2, print_err_quotes(), CONTINUE);
	return_code = expand_token_list(&token_list, minishell);
	if (return_code != OK)
		return (llstclear(&token_list, token_free), return_code);
	if (check_syntax(token_list) != 0)
		return (llstclear(&token_list, token_free), \
			minishell->status = 2, CONTINUE);
	minishell->ast = create_complete_command(token_list);
	llstclear(&token_list, token_free);
	if (minishell->ast == NULL)
		return (EXIT);
	return_code = manage_redirection(minishell);
	if (return_code != OK)
		return (return_code);
	if (manage_pipeline(minishell, minishell->ast) != 0)
		return (EXIT);
	minishell->status = execute_ast(minishell);
	return (free_loop(minishell), OK);
}

void	reader_loop(t_minishell *minishell)
{
	char	*line;

	g_last_signum = 0;
	set_prompt_signals();
	line = readline("minishell prompt % ");
	if (g_last_signum != 0)
		minishell->status = g_last_signum + 128;
	if (line == NULL)
		return (ft_putendl_fd("exit", 2));
	else if (is_str_blank(line))
		return (free(line), reader_loop(minishell));
	add_history(line);
	if (interpret_command(line, minishell) == EXIT)
		return (free(line), (void)(minishell->status = 1));
	return (free(line), reader_loop(minishell));
}
