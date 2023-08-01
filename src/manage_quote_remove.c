/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:06:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 17:41:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	remove_quote_word(t_token **token)
{
	char	*word;
	char	*word_without_quote;

	word = (*token)->data;
	word_without_quote = rm_peer_quotes(word);
	if (word_without_quote == NULL)
		return (ALLOC_FAIL);
	free(word);
	(*token)->data = word_without_quote;
	return (0);
}

int	manage_quote_remove(t_llist *token_list)
{
	t_llist	*current;
	t_token	*current_token;

	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (current_token->type == word && !is_prev_here_operator(current))
			if (remove_quote_word((t_token **)&(current->content)) != 0)
				return (ALLOC_FAIL);
		current = current->next;
	}
	return (0);
}
