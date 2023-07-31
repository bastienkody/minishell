/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/31 15:43:18 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_type	get_redirection_type(t_ntree *redirection_node)
{
	t_ntree *const	operator_node = redirection_node->children->content;
	t_ntree *const	type_node = operator_node->children->content;

	return (get_token(type_node)->type);
}

char	*get_redirection_filename(t_ntree *redirection_node)
{
	t_ntree *const	filename_node = redirection_node->children->next->content;
	t_ntree *const	word_node = filename_node->children->content;

	return (get_token(word_node)->data);
}

char	*get_here_end(t_ntree *here_doc_node)
{
	t_ntree *const	here_end_node = here_doc_node->children->content;
	t_ntree *const	word_node = here_end_node->children->content;

	return (get_token(word_node)->data);
}

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
		if (type == great || type == dgreat)
			fd = open_out(type, filename);
		else
			fd = open_in(filename);
	}
	return (fd);
}

int	open_in(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	return (fd);
}

int	open_out(t_type type, const char *filename)
{
	int	fd;

	if (type == great)
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else
		fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		perror("open outfile");
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
			if (redirection_type == less || redirection_type == dgreat || redirection_type == great)
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
