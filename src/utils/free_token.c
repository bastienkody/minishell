/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:38:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 14:06:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char g_data_token[] = {word, great, dgreat, less, dless, FILENAME, 0};

void	free_token(t_token *token)
{
	(free(token->data), free(token));
}

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
	else if (ft_strchr(g_data_token, type))
		free(token->data);
	free(token);
}