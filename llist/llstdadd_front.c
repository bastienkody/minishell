/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstdadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:30:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 23:49:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstadd_front(t_llist **llst, t_llist *new)
{
	if (*llst != NULL)
		(*llst)->prev = new;
	new->next = *llst;
	*llst = new;
}
