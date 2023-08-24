/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:51:25 by aguyon           ###   ########.fr       */
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

t_ntree	*leaf_new(const t_token *token)
{
	char *const	new_data = ft_strdup(token->data);

	if (new_data == NULL)
		return (NULL);
	return (ast_new(token->type, new_data, NULL));
}