/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:28:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 16:51:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int (*const	g_checkers[])(t_llist *)
	= {
	NULL,
	check_logical_operator,
	check_logical_operator,
	check_pipe,
	check_redirection,
	check_redirection,
	check_redirection,
	check_redirection,
	check_opening_parenthesis,
	check_closing_parenthesis,
};

static int	check_syntax_err(t_llist *token_list, char **operator_err)
{
	t_llist	*current;
	t_token	*current_token;

	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (current_token->type != word)
			if (g_checkers[current_token->type](current) != 0)
				return (*operator_err = current_token->data, -1);
		current = current->next;
	}
	return (*operator_err = NULL, 0);
}

int	check_syntax(t_llist *token_list)
{
	char	*operator_err;

	if (check_syntax_err(token_list, &operator_err) != 0)
		return (print_syntax_error(operator_err), -1);
	return (0);
}
