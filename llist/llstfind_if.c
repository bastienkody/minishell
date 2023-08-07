/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfind_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:25:50 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 17:48:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

// t_llist	*llstfind_if(t_llist *llst, int (*p)(void *))
// {
// 	while (llst != NULL)
// 	{
// 		if (p(llst->content))
// 			return (llst);
// 		llst = llst->next;
// 	}
// 	return (NULL);
// }

t_llist	*llstfind_if(t_llist *llst, int (*p)(void *))
{
	if (llst == NULL)
		return (NULL);
	if (p(llst->content))
		return (llst);
	return (llstfind_if(llst->next, p));
}

t_llist	*llstfind_if_range(t_llist *begin, t_llist *end, int (*p)(void *))
{
	if (begin == NULL || begin == end)
		return (NULL);
	if (p(begin->content))
		return (begin);
	return (llstfind_if_range(begin->next, end, p));
}