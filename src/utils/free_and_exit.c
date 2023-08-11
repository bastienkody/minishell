/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:17:52 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/11 14:29:43 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_and_exit(t_minishell *minishell)
{
	free_char_matrix(minishell->envp);
	ast_free(minishell->ast);
	exit(minishell->status);
}