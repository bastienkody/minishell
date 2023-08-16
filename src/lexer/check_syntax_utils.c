/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:54:57 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 20:55:32 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_opening_parenthesis(t_llist *node)
{
	t_token	*prev_token;
	t_token	*next_token;

	if (node->prev != NULL)
	{
		prev_token = node->prev->content;
		if (!is_type_inside(prev_token->type, (t_type[]){or, and, \
			opening_parenthesis, 0}))
			return (-1);
	}
	if (node->next == NULL)
		return (-1);
	next_token = node->next->content;
	if (!is_type_inside(next_token->type, (t_type[]){less, dless, \
		great, dgreat, word, opening_parenthesis, 0}))
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
	if (!is_type_inside(prev_token->type, (t_type[]){word, \
		closing_parenthesis, 0}))
		return (-1);
	if (node->next != NULL)
	{
		next_token = node->next->content;
		if (!is_type_inside(next_token->type, (t_type[]){and, or, \
			closing_parenthesis, 0}))
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
	if (!is_type_inside(prev_token->type, (t_type[]){word, \
		closing_parenthesis, 0}))
		return (-1);
	next_token = node->next->content;
	if (!is_type_inside(next_token->type, (t_type[]){word, \
		opening_parenthesis, 0}))
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
	if (!is_type_inside(next_token->type, (t_type[]){less, dless, \
		great, dgreat, word, 0}))
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
		if (!is_type_inside(prev_token->type, (t_type[]){or, and, ppipe, word, opening_parenthesis, 0}))
			return (-1);
	}
	if (node->next == NULL)
		return (-1);
	next_token = node->next->content;
	if (next_token->type != word)
		return (-1);
	return (0);
}
