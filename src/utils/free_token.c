/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:38:12 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/24 14:52:07 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char g_data_token[] = {word, great, dgreat, less, dless, FILENAME, 0};

void	free_token(t_token *token)
{
	(free(token->data), free(token));
}

void	free_node(t_token *token)
{
	const t_type	type = token->type;

	if (ft_strchr(g_data_token, type))
		free(token->data);
	free(token);
}