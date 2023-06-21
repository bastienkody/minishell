/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:34:15 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/21 13:30:40 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

static void	btree_apply_level(t_btree *root, t_tree_level_info info,
	bool *discovered_levels,
	void (*applyf)(void *item, int current_level, int is_first))
{
	if (root == NULL)
		return ;
	if (info.current_level == 1)
	{
		if (!discovered_levels[info.real_level])
		{
			applyf(root->item, info.real_level, true);
			discovered_levels[info.real_level] = true;
		}
		else
		{
			applyf(root->item, info.real_level, false);
		}
	}
	else if (info.current_level > 1)
	{
		info.current_level--;
		btree_apply_level(root->left, info, discovered_levels, applyf);
		btree_apply_level(root->right, info, discovered_levels, applyf);
	}
}

void	btree_apply_by_level(t_btree *root, void (*applyf)(void *item,
	int current_level, int is_first))
{
	int			i;
	const int	tree_levels = btree_level_count(root);
	bool		*discovered_levels;

	discovered_levels = ft_calloc(tree_levels + 1, sizeof(bool));
	if (discovered_levels == NULL)
		return ;
	i = 1;
	while (i <= tree_levels)
	{
		btree_apply_level(root, (t_tree_level_info){i, i},
			discovered_levels, applyf);
		i++;
	}
	free(discovered_levels);
}
