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

int	is_a_builtin(char **args)
{
	int					i;
	static const char	*b_name[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	static t_f			b_fct[7] = {&check_echo, &check_cd, &check_pwd,
		&check_export, &check_unset, &check_env, &check_exit};

	i = -1;
	while (b_name[++i])
	{
		if (!ft_strcmp(b_name[i], args[0]))
			return (intermed(args, b_fct[i]));
	}
	return (0);
}

int	exec_builtin(char **cmd_args, char ***envp)
{
	if (ft_strcmp(cmd_args[0], "echo"))
		return (echo(cmd_args));
	if (ft_strcmp(cmd_args[0], "cd"))
		return (cd(cmd_args[0], *envp));
	if (ft_strcmp(cmd_args[0], "pwd"))
		return (pwd());
	if (ft_strcmp(cmd_args[0], "export"))
		return (export(cmd_args, envp));
	if (ft_strcmp(cmd_args[0], "unset"))
		return (unset(cmd_args, envp));
	if (ft_strcmp(cmd_args[0], "env"))
		return (env(*envp, NULL));
	if (ft_strcmp(cmd_args[0], "exit"))
		return (exit_blt(cmd_args, *envp, NULL));
	return (1);
}
