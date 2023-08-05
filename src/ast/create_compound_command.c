/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compound_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:54:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/05 16:55:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_compound_command(t_llist *leaf)
{
	char *const	old_line = get_token(leaf->content)->data;
	char *const	new_line = ft_substr(old_line, 1, ft_strlen(old_line) - 2);
	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
	t_llist		*leaf_list;
	t_llist		*child;

	token_list = NULL;
	if (new_line == NULL)
		return (NULL);
	token_list = tokenization(new_line);
	free(new_line);
	if (token_list == NULL)
		return (NULL);
	leaf_list = token_to_leaf(token_list);
	if (leaf_list == NULL)
		return (NULL);
	// llstiter(leaf_list, (t_unary_fun)ast_print);
	if (llstfind_if(leaf_list, (t_predicate)is_node_logical_operator))
		child = create_child(leaf_list, create_logical_expression);
	else
		child = create_child(leaf_list, create_pipeline);
	if (child == NULL)
		return (llstclear(&leaf_list, ast_free), NULL);
	return (ast_new(COMPOUND_COMMAND, NULL, child));
}
