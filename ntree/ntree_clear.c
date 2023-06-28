/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:45:14 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/26 10:07:48 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

void	ntree_clear(t_ntree **ntree, void (*del)(void *))
{
	t_llist	*current_child;
	t_llist	*next_child;

	del((*ntree)->item);
	free(*ntree);
	current_child = (*ntree)->children;
	while (current_child != NULL)
	{
		next_child = current_child->next;
		ntree_clear((t_ntree **)&(current_child->content), del);
		current_child = next_child;
	}
	*ntree = NULL;
}
