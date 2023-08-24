/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:52:05 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:13:23 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static t_llist	*get_next_command(t_llist	*llist)
// {
// 	t_llist *const	pipe_pos
// 		= llstfind_if(*leaf_list, (t_predicate)is_token_pipe);
// 	t_llist *const	extract
// 		= llstextract_range(leaf_list, *leaf_list, pipe_pos);
// 	t_llist *const	command = create_child(extract, create_command);

// 	return (command);
// }

// static t_llist	*go_next_command(t_llist *llst)
// {
// 	t_llist	*pipe_pos;

// 	pipe_pos = llstfind_if(llst, (t_predicate)is_token_pipe);
// 	if (pipe_pos == NULL)
// 		return (NULL);
// 	return (pipe_pos->next);
// }

t_ntree	*create_pipeline(t_llist *begin, t_llist *end)
{
	t_llist	*children;
	t_llist	*child;
	t_llist	*current;
	t_llist	*pipe_pos;

	children = NULL;
	current = begin;
	while (current != NULL && current != end)
	{
		pipe_pos = llstfind_if_range(current, end, (t_predicate)is_token_pipe);
		if (pipe_pos == NULL)
			child = create_child_range(current, end, create_command);
		else
			child = create_child_range(current, pipe_pos, create_command);
		if (child == NULL)
			return (llstclear(&children, ast_free), NULL);
		llstadd_back(&children, child);
		if (pipe_pos == NULL)
			current = NULL;
		else
			current = pipe_pos->next;
	}
	return (ast_new(PIPELINE, NULL, children));
}
