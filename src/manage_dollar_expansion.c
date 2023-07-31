/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 13:38:29 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	expand_dollar_word(t_llist *node, char **envp, int last_status)
{
	char	*word;
	char	*expanded_word;
	t_token	*token;

	token = node->content;
	word = token->data;
	expanded_word = expand_dollar(word, envp, last_status);
	if (expanded_word == NULL)
		return (0);
	free(word);
	token->data = expanded_word;
	return (1);
}

int	is_str_redir(const char *str)
{
	return (is_str_great(str) || is_str_dgreat(str) || is_str_less(str));
}

int	is_prev_redir_operator(t_llist *node)
{
	t_token	*prev_token;

	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redir(prev_token->data) == 1);
}

int	manage_dollar_expansion(t_llist *token_list, char **envp, int last_status)
{
	t_llist	*current;
	t_token	*current_token;

	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (current_token->type == word && !is_prev_here_operator(current))
		{
			if (is_prev_redir_operator(current) && !check_amb_redir(current_token->data, envp))
				return (EAMBREDIR);
			if (!expand_dollar_word(current, envp, last_status))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
