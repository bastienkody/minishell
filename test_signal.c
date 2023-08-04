/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:24:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 23:26:18 by aguyon           ###   ########.fr       */
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

void	handle_sig_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sig_parent(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");

}

void	set_signal_prompt(void)
{
	signal(SIGINT, handle_sig_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_parent(void)
{
	signal(SIGINT, handle_sig_parent);
	signal(SIGQUIT, handle_sig_parent);
}

void	execute_command(char *command, char **envp)
{
	pid_t pid = fork();

	(void)command;
	if (pid == 0)
	{
		set_signal_child();
		execve("/bin/sleep", (char*[]){"/bin/sleep", "5", NULL}, envp);
	}
	else
	{
		set_signal_parent();
		wait(NULL);
	}
}

int read_command(char **envp)
{
	char *command;

	command = readline("prompt: ");
	if (command == NULL)
		return (-1);
	execute_command(command, envp);
	free(command);
	set_signal_prompt();
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	char *line;
	(void)argc;
	(void)argv;
	set_signal_prompt();
	while (1)
	{
		if (read_command(envp) == -1)
			return (0);
	}
	return (0);
}
