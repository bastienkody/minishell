/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstlast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:23:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 23:49:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstlast(t_llist *llst)
{
	if (llst != NULL)
		while (llst->next)
			llst = llst->next;
	return (llst);
}
