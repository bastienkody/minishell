/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:28:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/21 13:30:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	btree_level_count(t_btree *root)
{
	int	left_height;
	int	right_height;

	if (root == NULL)
		return (0);
	left_height = btree_level_count(root->left);
	right_height = btree_level_count(root->right);
	return (1 + max(left_height, right_height));
}
