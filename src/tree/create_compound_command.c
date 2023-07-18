/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compound_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:42:13 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 19:26:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*create_compound_command(t_llist *leaf)
{
	char *const	old_line = ((t_ast *)leaf->content)->data;
	char *const	new_line = ft_substr(old_line, 1, ft_strlen(old_line) - 2);
	t_llist		*token_list;
	t_llist		*leaf_list;
	t_llist		*child;

	llstclear(&leaf, (void (*)(void *))free_ast);
	if (new_line == NULL)
		return (NULL);
	token_list = lexer(new_line);
	free(new_line);
	if (token_list == NULL)
		return (NULL);
	leaf_list = token_to_leaf(token_list);
	llstclear(&token_list, (void (*)(void *))free_token);
	if (leaf_list == NULL)
		return (NULL);
	if (llstfind_if(leaf_list, (int (*)(void *))is_node_logical_operator))
		child = create_child(leaf_list, create_logical_expression);
	else
		child = create_child(leaf_list, create_pipeline);
	return (new_ast(COMPOUND_COMMAND, NULL, child));
}
