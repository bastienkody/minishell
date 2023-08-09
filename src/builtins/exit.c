/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/08 19:15:48 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_exit(char **args)
{
	return ((void) args, 1);
}

/*
	si pas d'arg : exit last status
	si premier argument str :
		- clean and exit
		- print "exit" on stdout
		- code 2
		- stderr : "bash: exit: abc: numeric argument required" abc is the first arg
	si premier arg est nb:
		si seul arg :
			- clean and exit
			- print "exit" on stdout
			- code = atoi_255(arg) (use unsigned byte)
		si poly arg :
			- do not clean and exit but still...
			- print "exit" on stdout
			- code 1
			- err : "bash: exit: too many arguments"


2 trucs chelous : 
	- dans bash : ls | exit does not output "exit" on stderr. it exits the fork (ok)
	- pas de pb dans minishell pour le return (vs un exit) quand exit avec poly numeric args.
*/

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

int	exit_blt(char **args, t_info *info)
{
	const char	*exit_msg = "exit\n";

	write(STDERR_FILENO, exit_msg, ft_strlen(exit_msg));
	if (!args[1])
		return (free_char_matrix(info->envp), ast_free(info->root_ast), exit(g_exit_status), g_exit_status);
	if (check_first_arg(args[1])) // first arg str
	{
		err_builtin(args[0], args[1], ERR_NMR);
		free_char_matrix(info->envp);
		ast_free(info->root_ast);
		g_exit_status = 2;
		exit(2);
	}
	if (args[1 + 1]) // poly args numeric
		return (err_msg(args[0], ERR_TMA), 1); // pb si appele dans dans un pipe/fork?
	free_char_matrix(info->envp);
	ast_free(info->root_ast); // solo arg numeric
	g_exit_status = (unsigned int) ft_atoi(args[1]);
	exit(g_exit_status);
}
