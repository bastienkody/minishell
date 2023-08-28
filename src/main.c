/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:51:36 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/28 12:25:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_last_signum;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	((void)argc, (void)argv);
	minishell = (t_minishell){};
	minishell.envp = charmatrix_dup(envp);
	if (minishell.envp == NULL)
		exit(1);
	reader_loop(&minishell);
	free_char_matrix(minishell.envp);
	exit(minishell.status);
}
