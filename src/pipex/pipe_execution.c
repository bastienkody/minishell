/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:44:48 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 14:44:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dupper(t_info *info, int prevpipe, int pipefd[2])
{
	int	old_fd;

	if (info->cmds->fd_in == NO_REDIR)
		old_fd = prevpipe;
	else if (info->cmds->fd_in > NO_REDIR)
	{
		close(prevpipe);
		old_fd = info->cmds->fd_in;
	}
	if (info->cmds->fd_in >= NO_REDIR && dup2(old_fd, STDIN) < 0)
		return (perror(ERR_DUP_IN), BAD_FD); // maybe exit_failure? we must end the program if syscall error
	close(old_fd);
	if (!info->cmds->next && info->cmds->fd_out == NO_REDIR)
		return (0);
	if (info->cmds->fd_out == NO_REDIR)
		old_fd = pipefd[1];
	else if (info->cmds->fd_out > NO_REDIR)
	{
		close(pipefd[1]);
		old_fd = info->cmds->fd_out;
	}
	if (info->cmds->fd_out >= NO_REDIR && dup2(old_fd, STDOUT) < 0)
		return (perror(ERR_DUP_OUT), BAD_FD);
	return (close(old_fd), 0);
}

void	in_child(t_info *info, int pipefd[2], int *prevpipe, t_minishell *minishell)
{
	close(pipefd[0]);
	if (!info->cmds->next)
		close(pipefd[1]);
	if (dupper(info, *prevpipe, pipefd) == BAD_FD)
		exit(EXIT_FAILURE); // on exit l'enfant ? quitter le prog parent aussi?
	if (info->cmds->fd_in > NO_REDIR)
		close (info->cmds->fd_in);
	if (info->cmds->fd_out > NO_REDIR)
		close (info->cmds->fd_out);
	execute(info->cmds->args, info, minishell);
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
	if (info->cmds->fd_in > NO_REDIR)
		close (info->cmds->fd_in);
	if (info->cmds->fd_out > NO_REDIR)
		close (info->cmds->fd_out);
}

void	fork_pipe_dup(int *prevpipe, t_info *info, t_minishell *minishell)
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
		set_child_signals();
		in_child(info, pipefd, prevpipe, minishell);
	}
	else if (pid > 0)
	{
		set_parent_signals();
		in_parent(info, pipefd, prevpipe, pid);
	}
}

int	pipex(t_minishell *minishell, t_info *info)
{
	int	prevpipe;

	if (!info->cmds->next && info->cmds->args && is_a_builtin(info->cmds->args, info->cmds->args[0]))
		return (exec_solo_builtin(info->cmds, minishell));
	prevpipe = dup(0);
	while (info->cmds)
	{
		fork_pipe_dup(&prevpipe, info, minishell);
		info->cmds = info->cmds->next;
	}
	wait_cmds(info);;
	return (analyze_status(info));
}
