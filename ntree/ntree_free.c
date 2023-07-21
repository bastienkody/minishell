/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:22:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 16:41:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

void	ntree_free(t_ntree *ntree, t_del_fun del)
{
	t_llist	*current;
	t_llist	*next;

	if (ntree == NULL)
		return ;
	del(ntree->data);
	current = ntree->children;
	while (current != NULL)
	{
		next = current->next;
		ntree_free(current->content, del);
		current = next;
	}
	free(ntree);
}
