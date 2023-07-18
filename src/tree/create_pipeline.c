/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:28:22 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/28 15:42:50 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_llist	*get_next_command(t_llist	**leaf_list)
{
	t_llist	*pipe_pos;
	t_llist	*command;

	pipe_pos = llstfind_if(*leaf_list, (int (*)(void *))is_node_pipe);
	command = create_child(llstextract_range(leaf_list, *leaf_list, pipe_pos), create_command);
	if (command == NULL)
		return (NULL);
	llstremoveone(leaf_list, pipe_pos, (void (*)(void *))free_ast);
	return (command);
}

t_ast	*create_pipeline(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;

	children = NULL;
	while (leaf_list != NULL)
	{
		child = get_next_command(&leaf_list);
		if (child == NULL)
			return (llstclear(&children, (void (*)(void *))free_ast), NULL);
		llstadd_back(&children, child);
	}
	return (new_ast(PIPELINE, NULL, children));
}

// t_ast	*create_pipeline(t_llist *leaf_list)
// {
// 	t_llist	*children;
// 	t_llist	*child;
// 	t_ast	*child_content;
// 	t_llist	*pipe;

// 	pipe = (void *)0x1;
// 	children = NULL;
// 	while (pipe != NULL)
// 	{
// 		pipe = llstfind_if(leaf_list, (int (*)(void *))is_token_pipe);
// 		child_content = create_command(llstextract_range(&leaf_list, leaf_list, pipe));
// 		if (child_content == NULL)
// 			return (NULL);
// 		child = llstnew(child_content);
// 		if (child == NULL)
// 			return (NULL);
// 		llstadd_back(&children, child);
// 		if (pipe != NULL)
// 			llstremoveone(&leaf_list, pipe, (void (*)(void *))free_ast);
// 	}
// 	return(new_ast(PIPELINE, NULL, children));
// }
