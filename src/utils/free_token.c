/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:38:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 17:10:57 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const size_t g_nb_data_token = 9;

static const t_type g_data_token[]
	= {word, ppipe, or, and, great, dgreat, less, dless, FILENAME};

// a modifier



void	free_pipex_info(t_info *pipex_info)
{
	cmd_clear(&(pipex_info->cmd_start));
	free(pipex_info);
}

void	free_node(t_token *token)
{
	const t_type	type = token->type;

	if (type == PIPELINE)
		free_pipex_info(token->data);
	else if (is_type_inside(token->type, g_data_token, g_nb_data_token))
		free(token->data);
	free(token);
}
