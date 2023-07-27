/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:52:55 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 18:01:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd_in(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_token	*current_token;
	t_type	redirection_type;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		current_token = get_token(current->content);
		if (current_token->type == REDIRECTION)
		{
			redirection_type = get_redirection_type(current->content);
			if (redirection_type == less)
				return ((intptr_t)(current_token->data));
		}
		else if (current_token->type == HERE_DOC)
		{
			return ((intptr_t)(current_token->data));
		}
		current = current->prev;
	}
	return (0);
}

int	get_fd_out(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_type	redirection_type;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		if (get_token(current->content)->type == REDIRECTION)
		{
			redirection_type = get_redirection_type(current->content);
			if (redirection_type == great || redirection_type == dgreat)
				return ((intptr_t)(get_token(current->content)->data));
		}
		current = current->prev;
	}
	return (0);
}
