/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:17:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/12 17:14:57 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_and_exit(t_minishell *minishell)
{
	free_char_matrix(minishell->envp);
	free_loop(minishell);
	exit(minishell->status);
}

void	free_loop(t_minishell *minishell)
{
	ast_free(minishell->ast);
	minishell->ast = NULL;
	llstiter(minishell->here_doc_files, (void *)remove_heredoc_tmpfile);
	llstclear(&minishell->here_doc_files, free);
}
