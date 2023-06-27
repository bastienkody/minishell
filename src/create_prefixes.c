/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prefixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:37:16 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 14:00:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*create_prefixes(t_llist *leaf_list)
{
	t_llist	*prefixes;
	t_llist	*new_child;
	t_ast	*new_ast;

	prefixes = NULL;
	if (llstsize(leaf_list) % 2 != 0)
		return (NULL);
	while (leaf_list != NULL)
	{
		new_ast = create_redirection(llstextract_range(&leaf_list, leaf_list, llstnext(leaf_list, 2)));
		if (new_ast == NULL)
			return (NULL);
		new_child = llstnew(new_ast);
		if (new_child == NULL)
			return (NULL);
		llstadd_back(&prefixes, new_child);
	}
	return (prefixes);
}
