/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compound_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:54:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 11:24:16 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// t_ntree	*create_compound_command(t_llist *leaf)
// {
// 	char *const	old_line = get_token(leaf->content)->data;
// 	char *const	new_line = ft_substr(old_line, 1, ft_strlen(old_line) - 2);
// 	__attribute__((cleanup(token_list_cleanup))) t_llist * token_list;
// 	t_llist		*leaf_list;
// 	t_llist		*child;
// 	// int			return_code;


// 	token_list = NULL;
// 	if (new_line == NULL)
// 		return (NULL);
// 	token_list = tokenization(new_line);
// 	free(new_line);
// 	if (token_list == NULL)
// 		return (NULL);
// 	// return_code = expand_token_list(&token_list, envp);
// 	// if (return_code == ALLOC_FAIL)
// 	// 	return (EXIT); // malloc error
// 	leaf_list = token_to_leaf(token_list);
// 	if (leaf_list == NULL)
// 		return (NULL);
// 	// llstiter(leaf_list, (t_unary_fun)ast_print);
// 	if (llstfind_if(leaf_list, (t_predicate)is_node_logical_operator))
// 		child = create_child_range(leaf_list, NULL, create_logical_expression);
// 	else
// 		child = create_child_range(leaf_list, NULL, create_pipeline);
// 	llstclear(&leaf_list, ast_free);
// 	if (child == NULL)
// 		return (NULL);
// 	return (ast_new(COMPOUND_COMMAND, NULL, child));
// }

t_ntree *create_compound_command(t_llist *begin, t_llist *end)
{
	t_llist *const	last = llstlast_range(begin, end);

	if (is_range_compound(begin->next, last))
		return (create_compound_command(begin->next, last));
	if (llstfind_if_range(begin, last, (t_predicate)is_node_logical_operator))
		return (create_logical_expression(begin->next, last));
	else
		return (create_pipeline(begin->next, last));
}

// (ls && (date))