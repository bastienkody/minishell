/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:24:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 15:39:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "inc/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		printf("\nCtrl-c pressed\n");
	else if (signum == SIGQUIT)
		printf("\nCtrl-\\ pressed\n");
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	char *line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("prompt: ");
		if (line == NULL)
			exit(0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fprintf(stderr, "execution : %s\n", line);
		sleep(5);
	}
	return (0);
}