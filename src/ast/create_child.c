/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:08:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 17:09:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_child(t_llist	*leaf, t_ntree *(*create)(t_llist *))
{
	t_ntree *const	subtree = create(leaf);

	if (subtree == NULL)
		return (NULL);
	return (llstnew(subtree));
}
