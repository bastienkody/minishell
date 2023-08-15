/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/15 13:59:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_type_str[]
	= {
	"dummy",
	"or",
	"and",
	"pipe",
	"great",
	"less",
	"dgreat",
	"dless",
	"opening_parenthesis",
	"closing_parenthesis",
	"word",
	"error",
	"amibougs_word",
	"COMPLETE_COMMAND",
	"COMPOUND_COMMAND",
	"LOGICAL_EXPRESSION",
	"PIPELINE",
	"SIMPLE_COMMAND",
	"CMD_NAME",
	"CMD_ARG",
	"CMD_PREFIX",
	"CMD_SUFFIX",
	"REDIRECTION",
	"OPERATOR",
	"FILENAME",
	"AND",
	"OR",
	"HERE_DOC",
	"HERE_END",
};

char	*type_to_string(t_type type)
{
	return ((char *)g_type_str[type]);
}

t_token	*get_token(t_ntree *ast)
{
	return (((t_token *)(ast->data)));
}

t_llist	*leaf_node_dup(t_llist *leaf_node)
{
	t_llist	*new_node;
	t_ntree	*new_leaf;

	new_leaf = ast_dup(leaf_node->content);
	if (new_leaf == NULL)
		return (NULL);
	new_node = llstnew(new_leaf);
	if (new_node == NULL)
		return (ast_free(new_leaf), NULL);
	return (new_node);
}
