/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstnext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:05:31 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 10:09:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstnext(t_llist *llist, size_t n)
{
	size_t	i;

	i = 0;
	while (llist != NULL && i < n)
	{
		llist = llist->next;
		i++;
	}
	return (llist);
}
