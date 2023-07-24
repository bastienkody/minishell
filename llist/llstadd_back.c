/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstadd_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:22:08 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/24 12:22:07 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstadd_back(t_llist **llst, t_llist *new)
{
	t_llist *const	last = llstlast(*llst);

	if (*llst == NULL)
		*llst = new;
	else
	{
		new->prev = last;
		last->next = new;
	}
}
