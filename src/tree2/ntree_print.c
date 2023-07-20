/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:26:00 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 16:11:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_node(t_ntree *ntree, int depth, void (*print)(void *))
{
	if (depth != 0)
		ft_fprintf(1, "+--- ");
	print(ntree->data);
	ft_fprintf(1, "\n");
}

static void	print_tree_rec(t_ntree *ntree, bool flag[256], size_t depth, int islast, void (*print)(void *))
{
	const t_llist	*current_child = ntree->children;
	size_t			i;

	if (ntree == NULL)
		return ;
	i = 0;
	while (++i < depth)
	{
		if (flag[i] == true)
			ft_fprintf(1, "|     ");
		else
			ft_fprintf(1, "     ");
	}
	if (depth == 0 || !islast)
		print_node(ntree, depth, print);
	else
		(print_node(ntree, depth, print), flag[depth] = false);
	while (current_child != NULL)
	{
		print_tree_rec(current_child->content,
			flag, depth + 1, current_child->next == NULL, print);
		current_child = current_child->next;
	}
	flag[depth] = true;
}


void	ntree_print(t_ntree *ntree, void (*print)(void *))
{
	bool	flag[256];

	ft_memset(flag, 1, 256);
	print_tree_rec(ntree, flag, 0, 0, print);
}

