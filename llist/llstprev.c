/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstprev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:07:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 10:09:02 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstprev(t_llist *llst, size_t n)
{
	size_t	i;

	i = 0;
	while (llst != NULL && i < n)
	{
		llst = llst->prev;
		i++;
	}
	return (llst);
}
