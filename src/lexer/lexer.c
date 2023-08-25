/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 13:13:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_newline_token(t_llist **token_list_ptr)
{
	char	*new_str;
	t_llist	*newline_node;

	new_str = ft_strdup("newline");
	if (new_str == NULL)
		return (-1);
	newline_node = llst_token_new(newline, new_str);
	if (newline_node == NULL)
		return (free(new_str), -1);
	llstadd_back(token_list_ptr, newline_node);
	return (0);
}

t_llist	*tokenization(const char *line)
{
	t_llist	*token_list;

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	llstremove_if(&token_list, (bool (*)(void *))is_str_blank, free);
	if (!llstreplace(&token_list, type_token(token_list), free))
		return (llstclear(&token_list, free), NULL);
	if (add_newline_token(&token_list) != 0)
		return (llstclear(&token_list, token_free), NULL);
	return (token_list);
}
