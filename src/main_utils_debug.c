/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:19:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 15:54:49 by aguyon           ###   ########.fr       */
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

t_token *llst_get_token(t_llist *node)
{
	return ((t_token *)node->content);
}

int	check_error(t_llist *token_list)
{
	char *operator_err;
	t_llist	*ambiguous_node;

	ambiguous_node = llstfind_if(token_list, (t_predicate)is_token_ambiguous_word);
	if (ambiguous_node != NULL)
		return (print_err_ambiguous(llst_get_token(ambiguous_node)->data), -1);
	if (llstfind_if(token_list, (t_predicate)is_token_error) != NULL)
		return (ft_fprintf(2, "minishell : token error\n"), -1);
	if (check_parenthesis_closed(token_list, &operator_err) != 0)
		return (print_syntax_error(operator_err), -1);
	if (check_syntax(token_list, &operator_err) != 0)
		return (print_syntax_error(operator_err), -1);
	return (0);
}

bool	is_word_quotes_closed(const char *str)
{
	bool		is_inside_quote;
	char	quote;

	is_inside_quote = false;
	quote = '\0';
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
		{
			if (is_inside_quote && *str == quote)
			{
				is_inside_quote = false;
				quote = '\0';
			}
			else if (!is_inside_quote)
			{
				is_inside_quote = true;
				quote = *str;
			}
		}
		str++;
	}
	return (!is_inside_quote);
}

bool	is_token_good(t_token *token)
{
	if (token->type == word && !is_word_quotes_closed(token->data))
		return (false);
	return (true);
}

t_state interpret_command(const char *line, t_minishell *minishell)
{
	int return_code;
	t_llist *token_list;

	token_list = tokenization(line);
	if (token_list == NULL)
		return (EXIT);
	if (!llstall_of(token_list, (void *)is_token_good))
		return (minishell->status = 2, print_err_quotes(), CONTINUE);
	return_code = expand_token_list(&token_list, minishell);
	if (return_code == EXIT)
		return (llstclear(&token_list, token_free), EXIT);
	if (return_code == CONTINUE)
		return (llstclear(&token_list, token_free), minishell->status = 0, CONTINUE);
	if (check_error(token_list) != 0)
		return (llstclear(&token_list, token_free), minishell->status = 2, CONTINUE);
	minishell->ast = parser(token_list);
	llstclear(&token_list, token_free);
	if (minishell->ast == NULL)
		return (EXIT);
	return_code = manage_here_doc(minishell->ast, minishell);
	if (return_code == EXIT)
		return (EXIT);
	if (return_code == CONTINUE)
		return (CONTINUE);
	manage_redir(minishell->ast, minishell->envp);
	if (manage_pipeline(minishell, minishell->ast) != 0)
		return (EXIT);
	minishell->status = execute_ast(minishell);
	return (free_loop(minishell), OK);
}

void	reader_loop(t_minishell *minishell)
{
	char *line;

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
