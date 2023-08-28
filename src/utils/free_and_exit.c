/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:17:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/28 15:13:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_heredoc_tmpfile(char *pathname)
{
	if (access(pathname, F_OK) == 0 && unlink(pathname) != 0)
		perror("unlink heredoc");
}

void	free_and_exit(t_minishell *minishell)
{
	free_char_matrix(minishell->envp);
	ast_free(minishell->ast);
	minishell->ast = NULL;
	exit(minishell->status);
}

void	free_and_exit_child(t_minishell *minishell)
{
	free_char_matrix(minishell->envp);
	ast_free(minishell->ast);
	minishell->ast = NULL;
	llstclear(&(minishell->here_doc_files), free);
	exit(minishell->status);
}

void	free_loop(t_minishell *minishell)
{
	ast_free(minishell->ast);
	minishell->ast = NULL;
	llstiter(minishell->here_doc_files, (void *)remove_heredoc_tmpfile);
	llstclear(&(minishell->here_doc_files), free);
}
