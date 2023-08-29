/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:38 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/29 12:31:12 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const t_type	g_data_token[]
	= {word, ppipe, or, opening_parenthesis, closing_parenthesis, and, great, \
		dgreat, less, dless, FILENAME, HERE_END, -1};

static void	free_pipex_info(t_info *pipex_info)
{
	if (pipex_info == NULL)
		return ;
	cmd_clear(&(pipex_info->cmd_start));
	free(pipex_info);
}

static void	free_node(t_token *token)
{
	t_type	type;

	if (token == NULL)
		return ;
	type = token->type;
	if (type == PIPELINE)
		free_pipex_info(token->data);
	else if (is_type_inside(type, g_data_token))
		free(token->data);
	free(token);
}

void	ast_free(t_ntree *ast)
{
	ntree_free(&ast, (t_del_fun)free_node);
}
