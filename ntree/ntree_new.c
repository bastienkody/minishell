/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:19:29 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 16:41:53 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ntree.h"

t_ntree	*ntree_new(void *data, t_llist *children)
{
	t_ntree *const	new = malloc(sizeof(t_ntree));

	if (new == NULL)
		return (NULL);
	*new = (t_ntree){data, children};
	return (new);
}
