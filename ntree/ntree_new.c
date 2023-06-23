/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:41:30 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/23 12:42:39 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

t_ntree	*ntree_new(void *item)
{
	t_ntree	*new;

	new = malloc(sizeof(t_ntree));
	if (new == NULL)
		return (NULL);
	*new = (t_ntree){item, NULL};
	return (new);
}