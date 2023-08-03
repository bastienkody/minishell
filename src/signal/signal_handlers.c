/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:01 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/03 10:47:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_prompt_signals(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	handle_parent_signals(int signum)
{
	if (signum == SIGINT)
		ft_putendl_fd("", 1);
	else if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
}

void	handle_here_doc_signals(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		close(0);
	}
}

