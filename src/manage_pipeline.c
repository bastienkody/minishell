/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:14:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:14:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	manage_pipeline(t_ntree *ast, char **envp)
{
	t_token	*token;
	t_llist	*current;

	if (ast == NULL)
		return (1);
	token = get_token(ast);
	if (token->type == PIPELINE)
	{
		token->data = get_pipex_info(ast, envp);
		if (token->data == NULL)
			return (0);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (!manage_pipeline(current->content, envp))
				return (0);
			current = current->next;
		}
	}
	return (1);
}
