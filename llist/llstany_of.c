/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstany_of.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:59:05 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/23 16:57:37 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstany_of(t_llist *llst, int (*p)(void *))
{
	if (llst == NULL)
		return (0);
	return (p(llst) || llstany_of(llst->next, p));
}
