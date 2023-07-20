/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 15:15:59 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_type	get_node_type(t_ntree *ntree)
{
	return (((t_token *)(ntree->data))->type);
}

static int is_node_inside(t_ntree *node, t_type types[], size_t n)
{
	const t_type type = get_node_type(node);
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (type == types[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_node_equal(t_ntree *node, t_type search_type)
{
	const t_type type = get_node_type(node);

	return (type == search_type);
}

int	is_node_compound(t_ntree *node)
{
	return (is_node_equal(node, compound));
}

int	is_node_logical_operator(t_ntree *node)
{
	return (is_node_inside(node, (t_type[]){or, and}, 2));
}

int	is_node_pipe(t_ntree *node)
{
	return (is_node_equal(node, ppipe));
}

int	is_node_word(t_ntree *node)
{
	return (is_node_equal(node, word));
}

int	is_node_redirection(t_ntree *node)
{
	return (is_node_inside(node, (t_type[]){less, dless, great, dgreat}, 4));
}