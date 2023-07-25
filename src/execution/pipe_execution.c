/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:44:48 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 17:05:06 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>

int	dupper(t_info *info, int prevpipe, int pipefd[2])
{
	int	old_fd;
	
	// infile
	if (info->cmds->fd_in == NO_REDIR)
		old_fd = prevpipe;
	else
		old_fd = info->cmds->fd_in;
	if (dup2(old_fd, STDIN) < 0)
		return (perror(ERR_DUP), BAD_FD); // maybe exit_failure? we must end the program if syscall error
	close(old_fd);
	// outfile
	if (info->cmds->fd_out == NO_REDIR)
		old_fd = pipefd[1];
	else
	 	old_fd = info->cmds->fd_out;
	if (dup2(old_fd, STDOUT) < 0)
		return (perror(ERR_DUP), BAD_FD);
	close(old_fd);
	return (0);
}

void	wait_cmds(t_info *info)
{
	int		child_status;
	pid_t	ret;

	ret = 0;
	while (ret != -1)
	{
		if (ret == info->last_pid)
			info->exit_code = child_status;
		ret = waitpid(-1, &child_status, 0);
	}
}

void	fork_pipe_dup(char **args, int *prevpipe, t_info *info)
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
		if (dupper(info, *prevpipe, pipefd) == BAD_FD)
			exit(EXIT_FAILURE); // on exit l'enfant ? quitter le prog parent aussi? 
		execute(args[0], args, info);
	}
	else if (pid > 0)
	{
		if (!info->cmds->next)
			info->last_pid = pid;
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
}

int	pipex(t_info *info)
{
	int	prevpipe;

	prevpipe = dup(0);
	while (info->cmds)
	{
		fork_pipe_dup(info->cmds->args, &prevpipe, info);
		info->cmds = info->cmds->next;
	}
	wait_cmds(info);
	return (analyze_status(info));
}
