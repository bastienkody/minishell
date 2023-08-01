/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstlast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:23:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 16:06:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstlast(const t_llist *llst)
{
	if (llst == NULL || llst->next == NULL)
		return ((t_llist *)llst);
	return (llstlast(llst->next));
}
