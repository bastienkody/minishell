/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_predicate_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:05:49 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 14:45:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_node_inside(t_token *token, t_type types[], size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (token->type == types[i])
			return (1);
		i++;
	}
	return (0);
}

bool	is_node_equal(t_token *token, t_type search_type)
{
	return (token->type == search_type);
}
