/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/01 16:03:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_node(t_ntree *node, char **envp, int last_status)
{
	t_type	type;
	char	*filename;
	char	*here_end;
	int		fd;

	if (get_token(node)->type == HERE_DOC)
	{
		here_end = get_here_end(node);
		fd = open_here_doc(here_end, envp, last_status);
	}
	else
	{
		type = get_redirection_type(node);
		filename = get_redirection_filename(node);
		fd = open_redirections(type, filename);
	}
	return (fd);
}

void	open_simple_command_redir(t_llist *child, char **envp, int last_status,
	int error)
{
	t_ntree	*current_node;
	t_token	*current_token;
	t_type	redirection_type;
	int		fd;

	if (child == NULL)
		return ;
	current_node = child->content;
	current_token = get_token(current_node);
	fd = -1;
	if (current_token->type == REDIRECTION)
	{
		if (error == 0)
		{
			redirection_type = get_redirection_type(current_node);
			if (ft_strchr((char []){less, dgreat, great, 0}, redirection_type))
			{
				fd = open_node(current_node, envp, last_status);
				if (fd == -1)
					error = 1;
			}
		}
		current_token->data = (void *)(intptr_t)fd;
	}
	open_simple_command_redir(child->next, envp, last_status, error);
}

void	manage_redir(t_ntree *ast, char **envp, int last_status)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;

	if (ast == NULL)
		return ;
	if (type == SIMPLE_COMMAND)
		open_simple_command_redir(ast->children, envp, last_status, 0);
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_redir(current->content, envp, last_status);
			current = current->next;
		}
	}
}

void	manage_here_doc(t_ntree *ast, char **envp, int last_status)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;
	int				fd;

	if (ast == NULL)
		return ;
	if (type == HERE_DOC)
	{
		fd = open_node(ast, envp, last_status);
		if (fd < 0)
			return ;
		get_token(ast)->data = (void *)(intptr_t)fd;
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_here_doc(current->content, envp, last_status);
			current = current->next;
		}
	}
}
