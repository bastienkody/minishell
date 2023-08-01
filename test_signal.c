/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:24:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 20:00:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "inc/minishell.h"
#include <unistd.h>
#include <sys/types.h>

int signalset = 0;

int read_command(char **envp);

void	sigint_handler(int signum)
{
	signalset = 1;
	printf("TEST");
	if (signum == SIGINT)
	{
		// printf("\nCtrl-c pressed\n");
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	sigchildhandler(int signum)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_redisplay();
// }

void	execute_command(char *command, char **envp)
{
	pid_t pid = fork();

	(void)command;
	if (pid == 0)
	{
		if (signalset)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
		execve("/bin/sleep", (char*[]){"/bin/sleep", "5", NULL}, envp);
	}
	else
		wait(NULL);
}

int read_command(char **envp)
{
	char *command;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	command = readline("prompt: ");
	if (command == NULL)
		return (-1);
	// signal(SIGINT, SIG_IGN);
	execute_command(command, envp);
	signalset = 0;
	free(command);
	printf("\n");
	// printf("%s\n", rl_line_buffer);
	rl_on_new_line();
	rl_replace_line("", 1);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	char *line;
	(void)argc;
	(void)argv;
	// rl_catch_signals = 0;
	// printf("%d\n", rl_catch_signals);
	while (1)
	{
		// if (signalset == 1)
		// {
		// 	rl_replace_line("", 0);
		// 	printf("\n");
		// 	rl_on_new_line();
		// 	rl_redisplay();
		// }
		if (read_command(envp) == -1)
			return (0);
	}
	return (0);
}