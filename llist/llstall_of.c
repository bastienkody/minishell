/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstall_of.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:56:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 11:34:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

bool	llstall_of(t_llist *llst, bool (*p)(void *))
{
	if (llst == NULL)
		return (1);
	return (p(llst->content) && llstall_of(llst->next, p));
}
