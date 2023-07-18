/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfind_if_not.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:23:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 23:24:18 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstfind_if_not(t_llist *llst, int (*p)(void *))
{
	while (llst != NULL)
	{
		if (!p(llst->content))
			return (llst);
		llst = llst->next;
	}
	return (NULL);
}
