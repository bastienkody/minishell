/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:44:48 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 14:44:50 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dupper(int old_fd, int new_fd)
{
	int	fd;

	fd = dup2(old_fd, new_fd) == -1;
	if (fd < -1)
	{
		perror(ERR_DUP);
		exit(EXIT_FAILURE);
	}
	close(old_fd);
	return (fd);
}

//files[0] = infile && files[0] = outfile;
void	fork_pipe_dup(char **args, int *prevpipe, int files[2], char **envp)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		perror(ERR_PIPE);
	pid = fork();
	if (pid == -1)
		perror(ERR_FORK); // + close n free ?
	if (pid == 0)
	{
		close(pipefd[0]);
		if (TRUE) // pas de redirection infile
			dupper(*prevpipe, STDIN);
		else
			dupper(files[0], STDIN);
		if (TRUE) // pas de rediction outfile
			dupper(pipefd[1], STDOUT);
		else
			dupper(files[1], STDOUT); 

		execute(args[0], args, envp);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
}

