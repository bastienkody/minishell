/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstremove_range.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:41:11 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 12:54:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstremove_range(t_llist **begin, t_llist *end, void (*del)(void *))
{
	t_llist	*temp;

	temp = llstextract_range(*begin, end);
	llstclear(&temp, del);
}
