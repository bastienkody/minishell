/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:28:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 16:55:47 by aguyon           ###   ########.fr       */
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

int	check_syntax(t_llist *token_list, char **operator_err)
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
