/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstreplace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:02:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/28 17:04:54 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

void	llstreplace(t_llist **original_list, t_llist *new_list, t_del_fun del)
{
	llstclear(original_list, del);
	*original_list = new_list;
}