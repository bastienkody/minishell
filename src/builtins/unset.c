/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:57 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/01 17:38:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_unset(char **args)
{
	(void)args;
	return (1);
}

static int	check_args(char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		if (ft_strlen(args[1]) > 1 && ft_strcmp(args[1], "--"))
		{
			err_builtin("unset", args[1], ERR_INVOPT);
			write(2, UNSET_USAGE, ft_strlen(UNSET_USAGE));
			return (0);
		}
	}
	return (1);
}

int	unset(char **args, char ***envp)
{
	if (!check_args(args))
		return (BUILTIN_ERR_CODE);
	args++;
	if (args && *args && !ft_strcmp(*args, "--"))
		args++;
	while (*args)
	{
		if (is_var_set(*args, *envp))
			if (supp_envar(*args, envp) == ALLOC_FAIL)
				return (ALLOC_FAIL);
		args++;
	}
	return (0);
}
