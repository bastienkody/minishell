/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:28:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 18:07:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int (*const g_checkers[])(t_llist *)
	= {
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
		if (current_token->type != word && g_checkers[current_token->type] != 0)
			return (*operator_err = current_token->data, -1);
		current = current->next;
	}
	return (*operator_err = NULL, 0);
}


int	check_opening_parenthesis(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev != NULL)
	{
		prev_token = node->prev->content;
		if (!is_type_inside(prev_token->type, (t_type[]){or, and, opening_parenthesis}))
			return (-1);
	}
	if (node->next == NULL)
		return (-1);
	next_token = node->next->content;
	if (!is_type_inside(next_token->type, (t_type[]){less, dless, great, dgreat, word, opening_parenthesis}))
		return (-1);
	return (0);
}

int	check_closing_parenthesis(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev == NULL)
		return (-1);
	prev_token = node->prev->content;
	if (!is_type_inside(prev_token->type, (t_type[]){word, closing_parenthesis}))
		return (-1);
	if (node->next != NULL)
	{
		next_token = node->next->content;
		if (!is_type_inside(next_token->type, (t_type[]){and, or, closing_parenthesis}))
			return (-1);
	}
	return (0);
}

int	check_logical_operator(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev == NULL || node->next == NULL)
		return (-1);
	prev_token = node->prev->content;
	if (!is_type_inside(prev_token->type, (t_type[]){word, closing_parenthesis}))
		return (-1);
	next_token = node->next->content;
	if (!is_type_inside(next_token->type, (t_type[]){word, opening_parenthesis}))
		return (-1);
	return (0);
}

int	check_pipe(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev == NULL || node->next == NULL)
		return (-1);
	prev_token = node->prev->content;
	if (prev_token->type != word)
		return (-1);
	next_token = node->next->content;
	if (!is_type_inside(next_token->type, (t_type[]){less, dless, great, dgreat, word}))
		return (-1);
	return (0);
}

int	check_redirection(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev != NULL)
	{
		prev_token = node->prev->content;
		if (!is_type_inside(prev_token->type, (t_type[]){or, and, word}))
			return (-1);
	}
	if (node->next == NULL)
		return (-1);
	next_token = node->next->content;
	if (next_token->type != word)
		return (-1);
	return (0);
}
