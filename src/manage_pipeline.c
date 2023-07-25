/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:14:06 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/25 15:18:17 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_pipeline(t_ntree *ast, char **envp)
{
	t_token	*token;
	t_llist	*current;

	if (ast == NULL)
		return ;
	token = get_token(ast);
	if (token->type == PIPELINE)
		token->data = get_pipex_info(ast, envp);
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_pipeline(current->content, envp);
			current = current->next;
		}
	}
}