/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:14:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 12:32:32 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	manage_pipeline(t_minishell *minishell, t_ntree *ast)
{
	t_token	*token;
	t_llist	*current;

	if (ast == NULL)
		return (0);
	token = get_token(ast);
	if (token->type == PIPELINE)
	{
		token->data = get_pipex_info(minishell, ast);
		if (token->data == NULL)
			return (1);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (manage_pipeline(minishell, current->content) != 0)
				return (1);
			current = current->next;
		}
	}
	return (0);
}
