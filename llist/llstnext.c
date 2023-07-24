/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstnext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:05:31 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/23 17:11:39 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstnext(t_llist *llist, size_t n)
{
	if (n == 0 || llist == NULL)
		return (llist);
	return (llstnext(llist->next, n - 1));
}
