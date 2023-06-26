/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:22 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/25 18:16:30 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NTREE_H
# define NTREE_H

#include "../llist/llist.h"

typedef struct s_ntree
{
	void	*item;
	t_llist	*children;
}	t_ntree;

void	ntree_add_children(t_ntree *ntree, t_llist	*children);
void	ntree_clear(t_ntree **ntree, void (*del)(void *));
t_ntree	*ntree_new(void *item);


#endif
