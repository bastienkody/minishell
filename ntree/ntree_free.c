/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:22:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 13:45:47 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

void	ntree_free(t_ntree **ntree, t_del_fun del)
{
	t_ntree	*current_node;
	t_llist	*current;
	t_llist	*next;

	current_node = *ntree;
	if (current_node == NULL)
		return ;
	del(current_node->data);
	current = current_node->children;
	while (current != NULL)
	{
		next = current->next;
		ntree_free((t_ntree **)&(current->content), del);
		free(current);
		current = next;
	}
	free(current_node);
	*ntree = NULL;
}
