/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/16 17:12:27 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_node_here_doc(t_ntree *node, t_minishell *minishell)
{
	char *const	here_end = get_here_end(node);

	return (open_here_doc(here_end, minishell));
}

int	open_node_redir(t_ntree *node)
{
	const t_type	type = get_redirection_type(node);
	char *const		filename = get_redirection_filename(node);

	return (open_redirections(type, filename));
}

void	open_simple_command_redir(t_llist *child, int error)
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
				fd = open_node_redir(current_node);
				if (fd == -1)
					error = 1;
			}
		}
		current_token->data = (void *)(intptr_t)fd;
	}
	open_simple_command_redir(child->next, error);
}

void	manage_redir(t_ntree *ast, char **envp)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;

	if (ast == NULL)
		return ;
	if (type == SIMPLE_COMMAND)
		open_simple_command_redir(ast->children, 0);
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_redir(current->content, envp);
			current = current->next;
		}
	}
}

t_state	manage_here_doc(t_ntree *ast, t_minishell *minishell)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;
	int				fd;
	int				return_code;

	if (ast == NULL)
		return (OK);
	if (type == HERE_DOC)
	{
		fd = open_node_here_doc(ast, minishell);
		if (fd == -3)
			return (CONTINUE);
		if (fd == -2)
			return (EXIT);
		get_token(ast)->data = (void *)(intptr_t)fd;
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			return_code = manage_here_doc(current->content, minishell);
			if (return_code != 0)
				return (return_code);
			current = current->next;
		}
	}
	return (OK);
}
