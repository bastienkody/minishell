/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prefixes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:59:37 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 16:44:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_prefixes(t_llist *begin, t_llist *end)
{
	t_llist	*prefixes;
	t_llist	*new_child;
	t_llist	*next;
	t_llist	*current;

	prefixes = NULL;
	if (llstsize_range(begin, end) % 2 != 0)
		return (NULL);
	current = begin;
	while (current != end)
	{
		next = llstnext(begin, 2);
		new_child = create_child_range(current, next, create_redirection);
		if (new_child == NULL)
			return (llstclear(&prefixes, ast_free), NULL);
		llstadd_back(&prefixes, new_child);
		current = next;
	}
	return (prefixes);
}
