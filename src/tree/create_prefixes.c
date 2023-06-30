/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prefixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:37:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/28 15:24:22 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_prefixes(t_llist *leaf_list)
{
	t_llist	*prefixes;
	t_llist	*new_child;

	prefixes = NULL;
	if (llstsize(leaf_list) % 2 != 0)
		return (NULL);
	while (leaf_list != NULL)
	{
		new_child = create_child(llstextract_range(&leaf_list, leaf_list, llstnext(leaf_list, 2)), create_redirection);
		if (new_child == NULL)
			return (llstclear(&prefixes, (void (*)(void *))free_ast), NULL);
		llstadd_back(&prefixes, new_child);
	}
	return (prefixes);
}
