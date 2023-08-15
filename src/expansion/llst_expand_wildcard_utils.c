/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_expand_wildcard_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:48:22 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 10:43:20 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (envp[i] + 4);
		i++;
	}
	return (NULL);
}

bool	is_prev_here_operator(t_llist *token_list)
{
	t_token	*prev_token;

	if (token_list->prev == NULL)
		return (0);
	prev_token = token_list->prev->content;
	return (ft_strcmp(prev_token->data, "<<") == 0);
}

t_llist	*node_dup(t_llist *node)
{
	const t_token	*original_token = node->content;
	t_llist			*new_node;
	t_token			*new_token;
	char			*new_str;

	new_str = ft_strdup(original_token->data);
	if (new_str == NULL)
		return (NULL);
	new_token = token_new(original_token->type, new_str);
	if (new_token == NULL)
		return (free(new_str), NULL);
	new_node = llstnew(new_token);
	if (new_node == NULL)
		return (token_free(new_token), NULL);
	return (new_node);
}
