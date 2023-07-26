/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:44:48 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/26 12:47:29 by aguyon           ###   ########.fr       */
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
	else if (info->cmds->fd_in > NO_REDIR)
		old_fd = info->cmds->fd_in;
	if (info->cmds->fd_in >= NO_REDIR && dup2(old_fd, STDIN) < 0)
		return (perror(ERR_DUP_IN), BAD_FD); // maybe exit_failure? we must end the program if syscall error
	close(old_fd);
	// outfileiif
	if (!info->cmds->next && info->cmds->fd_out == NO_REDIR)
		return (0);
	if (info->cmds->fd_out == NO_REDIR)
		old_fd = pipefd[1];
	else if (info->cmds->fd_out > NO_REDIR)
		old_fd = info->cmds->fd_out;
	if (info->cmds->fd_out >= NO_REDIR && dup2(old_fd, STDOUT) < 0)
		return (perror(ERR_DUP_OUT), BAD_FD);
	close(old_fd);
	return (0);
}

void	in_child(t_info *info, int pipefd[2], int *prevpipe)
{
	close(pipefd[0]);
	if (!info->cmds->next)
		close(pipefd[1]);
	if (dupper(info, *prevpipe, pipefd) == BAD_FD)
		exit(EXIT_FAILURE); // on exit l'enfant ? quitter le prog parent aussi?
	execute(info->cmds->args[0], info->cmds->args, info);
}

void	in_parent(t_info *info, int pipefd[2], int *prevpipe, int pid)
{
	if (!info->cmds->next)
	{
		close(pipefd[0]);
		info->last_pid = pid;
	}
	close(pipefd[1]);
	close(*prevpipe);
	*prevpipe = pipefd[0];
}

void	fork_pipe_dup(int *prevpipe, t_info *info)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd) == -1)
		perror(ERR_PIPE);
	//ft_fprintf(1, "cmd:%s\npipefd[0]:%i\npipefd[1]:%i\n", args[0], pipefd[0], pipefd[1]);
	pid = fork();
	if (pid == -1)
		perror(ERR_FORK); // + close n free ?
	if (pid == 0)
	{
		in_child(info, pipefd, prevpipe);
	}
	else if (pid > 0)
	{
		in_parent(info, pipefd, prevpipe, pid);
	}
}

int	pipex(t_info *info)
{
	int	prevpipe;

	prevpipe = dup(0);
	while (info->cmds)
	{
		fork_pipe_dup(&prevpipe, info);
		info->cmds = info->cmds->next;
	}
	wait_cmds(info);
	return (analyze_status(info));
}
