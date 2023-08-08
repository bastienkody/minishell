/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:06:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/08 17:13:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int	remove_quote_word(t_token **token)
// {
// 	char	*word;
// 	char	*word_without_quote;

// 	word = (*token)->data;
// 	word_without_quote = rm_peer_quotes(word);
// 	if (word_without_quote == NULL)
// 		return (1);
// 	free(word);
// 	(*token)->data = word_without_quote;
// 	return (0);
// }

// int	manage_quote_remove(t_llist *token_list)
// {
// 	t_llist	*current;
// 	t_token	*current_token;

// 	current = token_list;
// 	while (current != NULL)
// 	{
// 		current_token = current->content;
// 		if (current_token->type == word && !is_prev_here_operator(current))
// 			if (remove_quote_word((t_token **)&(current->content)) != 0)
// 				return (1);
// 		current = current->next;
// 	}
// 	return (0);
// }

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

t_llist	*llst_remove_quote(t_llist *token_list)
{
	t_llist	*new_token_list;
	t_llist	*new_node;
	t_llist	*current;
	t_token	*current_token;

	new_token_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (current_token->type == word && !is_prev_here_operator(current))
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
