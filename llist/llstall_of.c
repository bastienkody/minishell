/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstall_of.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:56:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/23 16:56:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstall_of(t_llist *llst, int (*p)(void *))
{
	if (llst == NULL)
		return (1);
	return (p(llst) && llstall_of(llst->next, p));
}
