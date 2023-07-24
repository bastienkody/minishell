/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:44:41 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/21 16:44:21 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NTREE_H
# define NTREE_H

# include "../libft/libft.h"
# include "../llist/llist.h"
# include "stdbool.h"
# include <string.h>

typedef struct s_ntree
{
	void	*data;
	t_llist	*children;
}	t_ntree;

typedef struct s_node_info
{
	int	depth;
	int	islast;
}	t_node_info;

t_ntree	*ntree_new(void *data, t_llist *children);
void	ntree_free(t_ntree *ntree, t_del_fun del);
void	ntree_print(t_ntree *ntree, void (*print)(void *));

#endif