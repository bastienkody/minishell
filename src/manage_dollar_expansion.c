/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:13:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char	g_expansible_node[] = {CMD_NAME, CMD_ARG, FILENAME, 0};

static int	expand_dollar_word(t_ntree *word_node, char **envp, int last_status)
{
	char	*word;
	char	*expanded_word;

	word = get_token(word_node)->data;
	expanded_word = expand_dollar(word, envp, last_status);
	if (expanded_word == NULL)
		return (0);
	free(word);
	get_token(word_node)->data = expanded_word;
	return (1);
}

int	manage_dollar_expansion(t_ntree *ast, char **envp, int last_status)
{
	t_type		type;
	t_llist		*current;

	if (ast == NULL)
		return (1);
	type = get_token(ast)->type;
	if (ft_strchr(g_expansible_node, type))
	{
		if (!expand_dollar_word(ast->children->content, envp, last_status))
			return (0);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (!manage_dollar_expansion(current->content, envp, last_status))
				return (0);
			current = current->next;
		}
	}
	return (1);
}
