/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_remove_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:06:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 12:01:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*remove_quote(char *str)
{
	char	*new_str;
	size_t	i;
	bool	is_inside_simple_quote;
	bool	is_inside_double_quote;

	new_str = malloc(ft_strlen(str) + 1);
	if (new_str == NULL)
		return (NULL);
	is_inside_simple_quote = false;
	is_inside_double_quote = false;
	i = 0;
	while (*str)
	{
		if (*str == '\'' && !is_inside_double_quote)
			is_inside_simple_quote = !is_inside_simple_quote;
		else if (*str == '\"' && !is_inside_simple_quote)
			is_inside_double_quote = !is_inside_double_quote;
		if (!(*str == '\'' && !is_inside_double_quote) \
			&& !(*str == '\"' && !is_inside_simple_quote))
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static t_llist	*get_remove_quote_node(t_llist *node)
{
	char	*new_data;
	t_token	*token;

	token = node->content;
	new_data = remove_quote(token->data);
	if (new_data == NULL)
		return (NULL);
	return (llst_token_new(word, new_data));
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
		if (llst_token_get_type(current) == word)
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
