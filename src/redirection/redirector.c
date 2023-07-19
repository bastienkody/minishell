/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/19 19:54:42 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_in(char *filename, char **envp)
{
	int	fd;

	if (!check_amb_redir(filename, envp))
		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
	filename = expand_dollar(filename, envp);
	if (!filename)
		return (MALLOC_FAIL_REDIR);
	if (access(filename, F_OK))
		return (err_msg(filename, ERR_NSFD), BAD_FD);
	if (access(filename, R_OK))
		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	// return (free(filename), fd);
	return (fd);
}


int	open_out(int type, char *filename, char **envp, t_ast *ast)
{
	int	fd;

	(void)ast;
	if (!check_amb_redir(filename, envp))
		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
	filename = expand_dollar(filename, envp);
	// printf("TEST : %s\n", (char *)((t_ast *)ast->children->next->content)->data);
	if (!filename)
		return (MALLOC_FAIL_REDIR);
	if (!access(filename, F_OK) && access(filename, W_OK))
		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
	fd = BAD_FD;
	if (type == great)
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (type == dgreat)
		fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		perror("open outfile");
	return (free(filename), fd);
}

void	manage_redir(t_ast *ast, char **envp)
{
	t_llist	*current;
	t_type	redir_type;
	char	*filename;

	if (ast == NULL)
		return ;
	if (ast->type != REDIRECTION || ast->data != NULL)
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_redir(current->content, envp);
			current = current->next;
		}
	}
	else
	{
		redir_type = (intptr_t)((t_ast *)ast->children->content)->data;
		filename = ((t_ast *)ast->children->next->content)->data;
		if (redir_type == great || redir_type == dgreat)
			ast->data = (void *)(intptr_t)(open_out(redir_type, filename, envp, ast));
		else if (redir_type == less)
			ast->data = (void *)(intptr_t)(open_in(filename, envp));
	}
}

void	manage_here_doc(t_ast *ast, char **envp)
{
	t_llist	*current;
	t_type redir_type;
	char *limiter;

	if (ast == NULL)
		return ;
	if (ast->type != REDIRECTION)
	{
		current = ast->children;
		while (current != NULL)
		{
			manage_here_doc(current->content, envp);
			current = current->next;
		}
	}
	else
	{
		redir_type = (intptr_t)((t_ast *)ast->children->content)->data;
		limiter = ((t_ast *)ast->children->next->content)->data;
		if (redir_type == dless)
			ast->data = (void *)(intptr_t)(open_here_doc(limiter, envp));
	}
}
