/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:36:03 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 15:48:01 by aguyon           ###   ########.fr       */
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

int	exec_builtin(char *cmd_name, char **args, char ***envp, t_info *info)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (echo(args));
	if (!ft_strcmp(cmd_name, "cd"))
		return (cd(args[1], *envp));
	if (!ft_strcmp(cmd_name, "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd_name, "export"))
		return (export(args, envp));
	if (!ft_strcmp(cmd_name, "unset"))
		return (unset(args, envp));
	if (!ft_strcmp(cmd_name, "env"))
		return (env(*envp, NULL));
	if (!ft_strcmp(cmd_name, "exit"))
		return (exit_blt(args, info));
	return (1);
}
