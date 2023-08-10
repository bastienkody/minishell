/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:14:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 12:43:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	manage_pipeline(t_ntree *ast, t_ntree *root, char **envp)
{
	t_token	*token;
	t_llist	*current;

	if (ast == NULL)
		return (0);
	token = get_token(ast);
	if (token->type == PIPELINE)
	{
		token->data = get_pipex_info(ast, root, envp);
		if (token->data == NULL)
			return (1);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (manage_pipeline(current->content, root, envp) != 0)
				return (1);
			current = current->next;
		}
	}
	return (0);
}
