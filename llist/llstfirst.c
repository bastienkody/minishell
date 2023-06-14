/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstfirst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:30:29 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 14:33:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstfirst(t_llist *llst)
{
	if (llstempty(llst))
		return (NULL);
	while (llst->prev != NULL)
		llst = llst->prev;
	return (llst);
}
