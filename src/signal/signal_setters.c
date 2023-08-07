/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:43:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/02 17:52:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_prompt_signals(void)
{
	signal(SIGINT, handle_prompt_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	set_parent_signals(void)
{
	signal(SIGINT, handle_parent_signals);
	signal(SIGQUIT, handle_parent_signals);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_here_doc_signals(void)
{
	signal(SIGINT, handle_here_doc_signals);
	signal(SIGQUIT, SIG_IGN);
}
