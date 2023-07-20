/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:22:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 16:10:39 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ntree_free(t_ntree *ntree, t_del_fun del)
{
	t_llist	*current;
	t_llist	*next;

	if (ntree == NULL)
		return ;
	del(ntree->data);
	current = ntree->children;
	while (current != NULL)
	{
		next = current->next;
		ntree_free(current->content, del);
		current = next;
	}
	free(ntree);
}

void	ast_free(t_ntree *ast)
{
	ntree_free(ast, (t_del_fun)free_token);
}