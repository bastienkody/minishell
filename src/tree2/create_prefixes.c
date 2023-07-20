/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prefixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:59:37 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 15:20:40 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_prefixes(t_llist *leaf_list)
{
	t_llist	*prefixes;
	t_llist	*new_child;
	t_llist	*extract;
	t_llist	*next;

	prefixes = NULL;
	if (llstsize(leaf_list) % 2 != 0)
		return (NULL);
	while (leaf_list != NULL)
	{
		next = llstnext(leaf_list, 2);
		extract = llstextract_range(&leaf_list, leaf_list, next);
		new_child = create_child(extract, create_redirection);
		if (new_child == NULL)
			return (llstclear(&prefixes, (t_del_fun)ntree_free), NULL);
		llstadd_back(&prefixes, new_child);
	}
	return (prefixes);
}