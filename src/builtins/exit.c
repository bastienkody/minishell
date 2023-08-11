/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 15:53:27 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_exit(char **args)
{
	return ((void) args, 1);
}

/* 1 str ; 0 nb */
int	check_first_arg(char *arg)
{
	if (arg[0] == '-' || arg[0] == '+')
		arg++;
	if (!*arg)
		return (1);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (1);
		arg++;
	}
	return (0);
}

int	exit_blt(char **args, t_minishell *minishell)
{
	const char		*exit_msg = "exit\n";
	long long int	code;

	write(STDERR_FILENO, exit_msg, ft_strlen(exit_msg));
	if (!args[1])
		free_and_exit(minishell);
	if (check_first_arg(args[1])) // first arg str
	{
		err_builtin(args[0], args[1], ERR_NMR);
		(minishell->status = 2, free_and_exit(minishell));
	}
	if (args[1 + 1])
		return (err_msg(args[0], ERR_TMA), 1);
	code = 0;
	if (ft_atoi_ll_novf(args[1], &code) == FALSE)
	{
		err_builtin(args[0], args[1], ERR_NMR);
		minishell->status = 2;
	}
	else
	{
		minishell->status = code;
	}
	return (free_and_exit(minishell), code);
}
