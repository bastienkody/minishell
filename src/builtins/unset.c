/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:44:14 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 14:44:16 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* builtin ret 1, execve ret 0 */
int	check_unset(char **args)
{
	if (args && args[1] && args[1][0] == '-' && ft_strlen(args[1]) > 1)
		return (0);
	return (1);
}

int	unset(char **args, char ***envp)
{
	args++;
	while (*args)
	{
		if (is_var_set(*args, *envp))
			if (supp_envar(*args, envp) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		args++;
	}
	return (0);
}
