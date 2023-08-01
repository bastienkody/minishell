/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:52:05 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 14:31:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_llist	*get_next_command(t_llist	**leaf_list)
{
	t_llist *const	pipe_pos
		= llstfind_if(*leaf_list, (t_predicate)is_node_pipe);
	t_llist *const	extract
		= llstextract_range(leaf_list, *leaf_list, pipe_pos);
	t_llist *const	command = create_child(extract, create_command);

	// if (command == NULL)
	// 	return (NULL);
	llstremoveone(leaf_list, pipe_pos, (t_del_fun)ast_free);
	return (command);
}

t_ntree	*create_pipeline(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;

	children = NULL;
	while (leaf_list != NULL)
	{
		child = get_next_command(&leaf_list);
		if (child == NULL)
			return (llstclear(&children, ast_free), NULL);
		llstadd_back(&children, child);
	}
	return (ast_new(PIPELINE, NULL, children));
}
