/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremoveone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:18:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 12:55:36 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremoveone(t_llist *llst, void (*del)(void *))
{
	t_llist	*temp;

	temp = llstextract(llst);
	llstclear(&temp, del);
}
