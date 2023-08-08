/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:52:55 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/08 13:40:48 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_fd_in(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_token	*current_token;
	int		fd;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		current_token = get_token(current->content);
		if (current_token->type == REDIRECTION)
		{
			if (get_redirection_type(current->content) == less)
			{
				fd = (intptr_t)(current_token->data);
				return (current_token->data = (void *)-2, fd);
			}
		}
		else if (current_token->type == HERE_DOC)
		{
			fd = (intptr_t)(current_token->data);
			return (current_token->data = (void *)-2, fd);
		}
		current = current->prev;
	}
	return (0);
}

int	get_fd_out(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_token	*current_token;
	t_type	redirection_type;
	int		fd;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		current_token = get_token(current->content);
		if (get_token(current->content)->type == REDIRECTION)
		{
			redirection_type = get_redirection_type(current->content);
			if (redirection_type == great || redirection_type == dgreat)
			{
				fd = (intptr_t)(current_token->data);
				current_token->data = (void *)-2;
				return (fd);
			}
		}
		current = current->prev;
	}
	return (0);
}
