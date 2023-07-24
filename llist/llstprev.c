/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstprev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:07:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/23 17:11:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstprev(t_llist *llst, size_t n)
{
	if (n == 0 || llst == NULL)
		return (llst);
	return (llstprev(llst->prev, n - 1));
}
