/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstextract_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:31:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/24 13:30:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"
#include <stdio.h>

t_llist	*llstextract_range(t_llist **begin_llst, t_llist *begin, t_llist *end)
{
	t_llist	*new;
	t_llist	*next;

	new = NULL;
	while (begin != end)
	{
		next = begin->next;
		llstadd_back(&new, llstextractone(begin_llst, begin));
		begin = next;
	}
	return (new);
}
