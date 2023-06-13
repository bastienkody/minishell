/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstsize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:19:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/13 17:21:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

size_t	llstsize(t_llist *llst)
{
	size_t len;

	len = 0;
	while (llst != NULL)
	{
		len++;
		llst = llst->next;
	}
	return (len);
}