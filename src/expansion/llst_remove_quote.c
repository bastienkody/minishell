/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_remove_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:06:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 17:08:28 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_llist	*get_remove_quote_node(t_llist *node)
{
	t_llist	*new_node;
	char	*new_data;
	t_token	*token;

	new_node = node_dup(node);
	if (new_node == NULL)
		return (NULL);
	token = new_node->content;
	new_data = rm_peer_quotes(token->data);
	if (new_data == NULL)
		return (llstdelone(new_node, (void *)token_free), NULL);
	free(token->data);
	token->data = new_data;
	return (new_node);
}

static bool	is_word_remove_quote(t_llist *node)
{
	t_token *const	token = node->content;

	return (token->type == word
		&& !is_prev_here_operator(node) && !is_str_empty_quote(token->data));
}

t_llist	*llst_remove_quote(t_llist *token_list)
{
	t_llist	*new_token_list;
	t_llist	*new_node;
	t_llist	*current;

	new_token_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		if (is_word_remove_quote(current))
			new_node = get_remove_quote_node(current);
		else
			new_node = node_dup(current);
		if (new_node == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_node);
		current = current->next;
	}
	return (new_token_list);
}
