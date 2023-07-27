/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:06:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:14:35 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char	g_expansible_node[] = {CMD_NAME, CMD_ARG, FILENAME, 0};

static int	remove_quote_word(t_ntree *word_node)
{
	char	*word;
	char	*word_without_quote;

	word = get_token(word_node)->data;
	word_without_quote = rm_peer_quotes(word);
	if (word_without_quote == NULL)
		return (0);
	free(word);
	get_token(word_node)->data = word_without_quote;
	return (1);
}

int	manage_quote_remove(t_ntree *ast)
{
	t_type		type;
	t_llist		*current;

	if (ast == NULL)
		return (1);
	type = get_token(ast)->type;
	if (ft_strchr(g_expansible_node, type))
	{
		if (!remove_quote_word(ast->children->content))
			return (0);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (!manage_quote_remove(current->content))
				return (0);
			current = current->next;
		}
	}
	return (1);
}
