/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:01:54 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 11:42:25 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_type_str[]
	= {
	"or",
	"and",
	"pipe",
	"great",
	"less",
	"dgreat",
	"dless",
	"compound",
	"word",
	"error",
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
