/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:16:04 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/26 10:37:34 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*new_leaf(t_token *token)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	*new = (t_node){token->type, {.text = token->text}};
	return (new);
}

int	shift(t_llist	*tree_list, t_llist	*token_list)
{
	t_node	*new_content;
	t_ntree	*new_node;
	t_llist	*new_llst;
	t_llist	*extract;

	extract = llstextractone(&token_list, token_list);
	new_content = new_leaf(extract);
	if (new_content == NULL)
		return (0);
	new_node = ntree_new(new_content);
	if (new_node == NULL)
		return (0);
	new_llst = llstnew(new_node);
	if (new_llst == NULL)
		return (0);
	return (1);
}