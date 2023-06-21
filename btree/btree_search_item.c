/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:21:58 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/21 13:15:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
	int (*cmpf)(void *, void *))
{
	if (root == NULL)
		return (NULL);
	else
	{
		if (cmpf(data_ref, root->item) == 0)
			return (root->item);
		else if (cmpf(data_ref, root->item) > 0)
			return (btree_search_item(root->right, data_ref, cmpf));
		else
			return (btree_search_item(root->left, data_ref, cmpf));
	}
}
