/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:28:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/17 15:18:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_token_word(t_token *token)
{
	return (token->type == word);
}

static int	is_token_redirection_operator(t_token *token)
{
	const t_type	type = token->type;

	return (type == less || type == great || type == dless || type == dgreat);
}

static int	is_token_pipe(t_token *token)
{
	return (token->type == ppipe);
}

static int	is_token_logical_operator(t_token *token)
{
	const t_type	type = token->type;

	return (type == and || type == or);
}

static int	is_token_operator(t_token *token)
{
	return (is_token_logical_operator(token) || is_token_pipe(token));
}

int	check_syntax(t_llist *token_list)
{
	t_llist	*current;

	current = token_list;
	while (current != NULL)
	{
		if (is_token_pipe(current->content) || is_token_logical_operator(current->content))
		{
			if (current->prev == NULL || current->next == NULL)
				return (0);
			if (is_token_operator(current->prev->content) || is_token_operator(current->next->content))
				return (0);
		}
		else if (is_token_redirection_operator(current->content))
		{
			if (current->next->content == NULL)
				return (0);
			if (!is_token_word(current->next->content))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
