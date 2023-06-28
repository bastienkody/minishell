/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:14:22 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 14:14:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*create_child(t_llist	*leaf, t_ast *(*create)(t_llist *))
{
	t_ast	*subtree;

	subtree = create(leaf);
	if (subtree == NULL)
		return (NULL);
	return (llstnew(subtree));
}
