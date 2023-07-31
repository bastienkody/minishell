/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:36:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/29 16:57:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	expand_dollar_word(t_token **token, char **envp, int last_status)
{
	char	*word;
	char	*expanded_word;

	word = (*token)->data;
	expanded_word = expand_dollar(word, envp, last_status);
	if (expanded_word == NULL)
		return (0);
	free(word);
	(*token)->data = expanded_word;
	return (1);
}

int	manage_dollar_expansion(t_llist *token_list, char **envp, int last_status)
{
	t_llist	*current;
	t_token	*current_token;

	current = token_list;
	while (current != NULL)
	{
		current_token = current->content;
		if (!check_amb_redir(current_token->data, envp))
			return (puts("Error dollar expansion\n"), 0);
		if (current_token->type == word && !is_prev_here_operator(current))
			if (!expand_dollar_word((t_token **)&(current->content), envp, last_status))
				return (0);
		current = current->next;
	}
	return (1);
}
