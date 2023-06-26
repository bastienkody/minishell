/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:53:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/25 19:41:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*new_leaf(t_type type, t_token *token)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	*new = (t_node){type, {.text = token->text}};
	return (new);
}

static t_ntree	*f(t_token *token)
{
	t_node	*node;

	node = new_leaf(token->type, token);
	if (node == NULL)
		return (NULL);
	return(ntree_new(node));
}

t_llist	*token_to_tree(t_llist	*token_list)
{
	return(llstmap(token_list, (void *(*)(void *))f, free));
}
