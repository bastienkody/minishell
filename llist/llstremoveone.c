/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremoveone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:18:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/23 15:35:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremoveone(t_llist **begin, t_llist *llst, void (*del)(void *))
{
	llst = llstextractone(begin, llst);
	llstclear(&llst, del);
}
