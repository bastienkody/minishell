/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:24:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 11:45:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "inc/minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\nCtrl-c pressed\n");
	else if (signal == SIGQUIT)
		printf("\nCtrl-\\ pressed\n");
}

int	main(void)
{
	char *line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		line = readline("prompt: ");
		if (line == NULL)
			exit(0);
		printf("%s", line);
	}
	return (0);
}