/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_predicate_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:05:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 10:46:12 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_node_inside(t_ntree *node, t_type types[], size_t n)
{
	const t_type	type = get_token(node)->type;
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (type == types[i])
			return (1);
		i++;
	}
	return (0);
}

bool	is_node_equal(t_ntree *node, t_type search_type)
{
	const t_type	type = get_token(node)->type;

	return (type == search_type);
}
