/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:18:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 16:57:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*ast_new(t_type type, void *data, t_llist *children)
{
	t_token	*new_token;
	t_ntree	*new_ntree;

	new_token = token_new(type, data);
	if (new_token == NULL)
		return (NULL);
	new_ntree = ntree_new(new_token, children);
	if (new_ntree == NULL)
		return (free_token(new_token), NULL);
	return (new_ntree);
}
