/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:28:22 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/27 23:07:07 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int is_token_pipe(t_token *token)
{
	return (token->type == ppipe);
}

static void free_ast(t_ast	*ast)
{
	free(ast->data);
}

static t_llist	*get_next_command(t_llist	*leaf_list)
{
	t_llist	*pipe_pos;
	t_llist	*command;

	pipe_pos = llstfind_if(leaf_list, (int (*)(void *))is_token_pipe);
	if (llstempty(leaf_list) || (pipe_pos == NULL && (pipe_pos->next == NULL || pipe_pos->prev == NULL)))
		return (NULL);
	command = create_child(llstextract_range(&leaf_list, leaf_list, pipe_pos), create_command);
	if (command == NULL)
		return (NULL);
	llstremoveone(&leaf_list, pipe_pos, free);
	return (command);
}

t_ast	*create_pipeline(t_llist *leaf_list)
{
	t_llist	*children;
	t_llist	*child;

	while (leaf_list == NULL)
	{
		child = get_next_commands(leaf_list);
		if (child == NULL)
			return (NULL);
		llstadd_back(&children, child);
	}
	return(new_ast(PIPELINE, NULL, children));
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
