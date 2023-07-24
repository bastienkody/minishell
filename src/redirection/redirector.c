/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 15:16:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_type get_redirection_type(t_ntree *redirection_node)
{
	t_ntree *const	operator_node = redirection_node->children->content;
	t_ntree *const	type_node = operator_node->children->content;

	return (get_token(type_node)->type);
}

char *get_redirection_filename(t_ntree *redirection_node)
{
	t_ntree *const	filename_node = redirection_node->children->next->content;
	t_ntree *const	word_node = filename_node->children->content;

	return (get_token(word_node)->data);
}

int	open_node(t_ntree *node, char **envp)
{
	const t_type	type = get_redirection_type(node);
	const char	*filename = get_redirection_filename(node);
	int			fd;

	if (type == great || type == dgreat)
		fd = open_out(type, filename);
	else if (type == less)
		fd = open_in(filename);
	else
		fd = open_here_doc(filename, envp);
	return (fd);
}

int open_in(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	return (fd);
}

int open_out(t_type type, const char *filename)
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

// int	open_in(char *filename, char **envp)
// {
// 	int	fd;

// 	if (!check_amb_redir(filename, envp))
// 		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
// 	filename = expand_dollar(filename, envp);
// 	if (!filename)
// 		return (MALLOC_FAIL);
// 	if (access(filename, F_OK))
// 		return (err_msg(filename, ERR_NSFD), BAD_FD);
// 	if (access(filename, R_OK))
// 		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		perror("open infile");
// 	// return (free(filename), fd);
// 	return (fd);
// }


// int	open_out(int type, char *filename, char **envp)
// {
// 	int	fd;

// 	if (!check_amb_redir(filename, envp))
// 		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
// 	filename = expand_dollar(filename, envp);
// 	if (!filename)
// 		return (MALLOC_FAIL);
// 	if (!access(filename, F_OK) && access(filename, W_OK))
// 		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
// 	fd = BAD_FD;
// 	if (type == great)
// 		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 00644);
// 	else if (type == dgreat)
// 		fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 00644);
// 	if (fd < 0)
// 		perror("open outfile");
// 	return (free(filename), fd);
// }

// void	manage_redir(t_ast *ast, char **envp)
// {
// 	t_llist	*current;
// 	t_type	redir_type;
// 	char	*filename;

// 	if (ast == NULL)
// 		return ;
// 	if (ast->type != REDIRECTION || ast->data != NULL)
// 	{
// 		current = ast->children;
// 		while (current != NULL)
// 		{
// 			manage_redir(current->content, envp);
// 			current = current->next;
// 		}
// 	}
// 	else
// 	{
// 		redir_type = (intptr_t)((t_ast *)ast->children->content)->data;
// 		filename = ((t_ast *)ast->children->next->content)->data;
// 		if (redir_type == great || redir_type == dgreat)
// 			ast->data = (void *)(intptr_t)(open_out(redir_type, filename, envp, ast));
// 		else if (redir_type == less)
// 			ast->data = (void *)(intptr_t)(open_in(filename, envp));
// 	}
// }

void	manage_redir(t_ntree *ast, char **envp)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;
	t_type			redirection_type;

	if (ast == NULL)
		return ;
	if (type == REDIRECTION)
	{
		redirection_type = get_redirection_type(ast);
		if (redirection_type == less || redirection_type == dgreat || redirection_type == great)
			get_token(ast)->data = (void *)(intptr_t)open_node(ast, envp);
	}
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

void	manage_here_doc(t_ntree *ast, char **envp)
{
	t_llist			*current;
	const t_type	type = get_token(ast)->type;
	t_type			redirection_type;

	if (ast == NULL)
		return ;
	if (type == REDIRECTION)
	{
		redirection_type = get_redirection_type(ast);
		if (redirection_type == dless)
			get_token(ast)->data = (void *)(intptr_t)open_node(ast, envp);
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_here_doc(current->content, envp);
			current = current->next;
		}
	}
}

// void	manage_here_doc(t_ast *ast, char **envp)
// {
// 	t_llist	*current;
// 	t_type redir_type;
// 	char *limiter;

// 	if (ast == NULL)
// 		return ;
// 	if (ast->type != REDIRECTION)
// 	{
// 		current = ast->children;
// 		while (current != NULL)
// 		{
// 			manage_here_doc(current->content, envp);
// 			current = current->next;
// 		}
// 	}
// 	else
// 	{
// 		redir_type = (intptr_t)((t_ast *)ast->children->content)->data;
// 		limiter = ((t_ast *)ast->children->next->content)->data;
// 		if (redir_type == dless)
// 			ast->data = (void *)(intptr_t)(open_here_doc(limiter, envp));
// 	}
// }
