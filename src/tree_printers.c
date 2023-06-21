/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:24:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/21 13:24:24 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_level(t_btree *node)
{
	if (!node)
		return ;
	ft_putendl_fd(node->item, 1);
	while (node->right)
	{
		node = node->right;
		ft_putendl_fd(node->item, 1);
	}
}

void	print_tree_as_cmd_line(t_btree *start)
{
	if (!start)
		return ;
	while (start->left)
	{
		print_tree_as_cmd_line(start->left);
		print_level(start);
	}
}
