/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:43:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/25 19:50:07 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	reduce(t_llist	*tree_list, int n, t_node	*node)
{
	t_llist	*extract;
	t_ntree	*replace_tree;
	t_llist	*replace_node;

	extract = llstextract_range(&tree_list, llstnext(tree_list, n));
	replace_tree = ntree_new(node);
	if (replace_tree == NULL)
		return (0);
	replace_node = llstnew(replace_tree);
	if (replace_node == NULL)
		return (0);
	llstadd_front(&tree_list, replace_node);
	return (1);
}
