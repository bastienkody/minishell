/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llstreplace_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:30:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 17:33:46 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llist.h"

t_llist	*llstreplace_range(t_llist **begin1, t_llist **last, t_llist *begin2, t_llist *end2)
{
	*begin1 = begin2;
}