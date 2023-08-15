/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:08:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 15:55:37 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*create_child_range(t_llist	*begin, t_llist	*end, \
t_ntree *(*create)(t_llist *, t_llist *))
{
	t_ntree *const	subtree = create(begin, end);

	if (subtree == NULL)
		return (NULL);
	return (llstnew(subtree));
}

t_llist	*create_child(t_llist *llist, t_ntree *(create)(t_llist *))
{
	t_ntree *const	subtree = create(llist);

	if (subtree == NULL)
		return (NULL);
	return (llstnew(subtree));
}
