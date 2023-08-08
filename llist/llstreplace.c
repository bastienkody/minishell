/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstreplace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:02:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/08 16:54:32 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

int	llstreplace(t_llist **original_list, t_llist *new_list, void *del)
{
	llstclear(original_list, del);
	if (new_list == NULL)
		return (0);
	*original_list = new_list;
	return (1);
}
