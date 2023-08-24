/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_word_splitting_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:27:46 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 12:31:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_prev_redir_operator(t_llist *node)
{
	t_token	*prev_token;

	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redirection(prev_token->data) == 1);
}

t_llist	*new_field_node(char *str, size_t start, size_t len)
{
	char	*new_str;

	new_str = ft_substr(str, start, len);
	if (new_str == NULL)
		return (NULL);
	return (llst_token_new(word, new_str));
}
