/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_close_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:31:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/29 12:31:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ast_close_fd(t_ntree *ast)
{
	t_token	*token;
	t_llist	*current_child;
	int		fd;

	if (ast == NULL)
		return ;
	token = get_token(ast);
	if (token->type == HERE_DOC || token->type == REDIRECTION)
	{
		fd = (intptr_t)token->data;
		if (fd > 0)
		{
			close(fd);
			token->data = (void *)-1;
		}
	}
	else
	{
		current_child = ast->children;
		while (current_child)
		{
			ast_close_fd(current_child->content);
			current_child = current_child->next;
		}
	}
}

static void	redir_close_unused_fd(t_ntree *node, bool *infile_find,
	bool *outfile_find)
{
	t_token	*token;
	int		fd;

	token = node->data;
	fd = (intptr_t)token->data;
	if (token->type == HERE_DOC || get_redirection_type(node) == less)
	{
		if (*infile_find && fd > 0)
		{
			close(fd);
			token->data = (void *)-1;
		}
		*infile_find |= true;
	}
	else
	{
		if (*outfile_find && fd > 0)
		{
			close(fd);
			token->data = (void *)-1;
		}
		*outfile_find |= true;
	}
}

static void	command_close_unused_fds(t_llist *command)
{
	bool	infile_find;
	bool	outfile_find;
	t_llist	*current;
	t_token	*current_token;

	infile_find = false;
	outfile_find = false;
	current = llstlast(command);
	while (current != NULL)
	{
		current_token = get_token(current->content);
		if (current_token->type == HERE_DOC \
			|| current_token->type == REDIRECTION)
			redir_close_unused_fd(current->content, &infile_find, \
				&outfile_find);
		current = current->prev;
	}
}

void	ast_close_unused_fds(t_ntree *ast)
{
	t_token	*token;
	t_llist	*current_child;

	if (ast == NULL)
		return ;
	token = get_token(ast);
	if (token->type == SIMPLE_COMMAND)
		command_close_unused_fds(ast->children);
	else
	{
		current_child = ast->children;
		while (current_child != NULL)
		{
			ast_close_unused_fds(current_child->content);
			current_child = current_child->next;
		}
	}
}
