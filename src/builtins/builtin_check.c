/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:36:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 14:51:04 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	intermed(char **args, int (*f)(char **))
{
	return (f(args));
}

int	is_a_builtin(char **args, char *cmd_name)
{
	int					i;
	static const char	*b_name[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	static t_f			b_fct[7] = {&check_echo, &check_cd, &check_pwd,
		&check_export, &check_unset, &check_env, &check_exit};

	i = -1;
	while (b_name[++i])
	{
		if (!ft_strcmp(b_name[i], cmd_name))
			return (intermed(args, b_fct[i]));
	}
	return (0);
}

int	exec_builtin(char *cmd_name, char **args, t_minishell *minishell)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (echo(args));
	if (!ft_strcmp(cmd_name, "cd"))
		return (cd(args[1], minishell->envp));
	if (!ft_strcmp(cmd_name, "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd_name, "export"))
		return (export(args, &minishell->envp));
	if (!ft_strcmp(cmd_name, "unset"))
		return (unset(args, &minishell->envp));
	if (!ft_strcmp(cmd_name, "env"))
		return (env(minishell->envp, NULL, 0));
	if (!ft_strcmp(cmd_name, "exit"))
		return (exit_blt(args, minishell));
	return (1);
}

int	redir_solo_builtin(t_cmd *cmd)
{
	if (cmd->fd_in > NO_REDIR && dup2(cmd->fd_in, STDIN) < 0)
		return (perror(ERR_DUP_IN), BAD_FD);
	close(cmd->fd_in);
	if (cmd->fd_out > NO_REDIR && dup2(cmd->fd_out, STDOUT) < 0)
		return (perror(ERR_DUP_OUT), BAD_FD);
	close(cmd->fd_out);
	return (1);
}

int	exec_solo_builtin(t_cmd *cmd, t_minishell *minishell)
{
	int	old_stdin;
	int	old_stdout;

	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return (minishell->status = 1, 1);
	if (cmd->fd_in > NO_REDIR || cmd->fd_out > NO_REDIR)
	{
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		if (redir_solo_builtin(cmd) < 0)
			return (BAD_FD);
	}
	minishell->status = exec_builtin(cmd->args[0], cmd->args, minishell);
	if (cmd->fd_in > NO_REDIR || cmd->fd_out > NO_REDIR)
	{
		dup2(old_stdin, STDIN_FILENO);
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdin);
		close(old_stdout);
	}
	return (minishell->status);
}
