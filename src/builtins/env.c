/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:13:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 14:14:03 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env(char **args)
{
	if (args[1])
		return (0);
	return (1);
}

int	env(char **envp, char *prefix)
{
	static const char	nl = '\n';
	int					i;

	i = -1;
	while (envp && envp[++i])
	{
		if (prefix)
			if (write(1, prefix, ft_strlen(prefix)) < 0)
				return (BUILTIN_ERR_CODE);
		if (write(1, envp[i], ft_strlen(envp[i])) < 0 || write(1, &nl, 1) < 0)
			return (BUILTIN_ERR_CODE);
	}
	return (0);
}
