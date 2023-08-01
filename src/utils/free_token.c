/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:38:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 16:04:45 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char	g_data_token[]
	= {word, ppipe, great, dgreat, less, dless, FILENAME, 0};

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
	else if (ft_strchr(g_data_token, type))
		free(token->data);
	free(token);
}
