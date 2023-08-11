/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:13:59 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/10 20:42:14 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_env(char **args)
{
	if (args[1])
		return (0);
	return (1);
}

int	print_variable(const char *str, const char *prefix, int quote)
{
	char *const	pos_equal = ft_strchr(str, '=');

	if (prefix)
		if (write(1, prefix, ft_strlen(prefix)) < 0)
			return (-1);
	if (write(1, str, pos_equal - str + 1) < 0)
		return (-1);
	if (quote)
		if (write(1, "\"", 1) < 0)
			return (-1);
	if (write(1, pos_equal + 1, ft_strlen(pos_equal + 1)) < 0)
		return (-1);
	if (quote)
		if (write(1, "\"", 1) < 0)
			return (-1);
	if (write(1, "\n", 1) < 0)
		return (-1);
	return (0);
}

int	env(char **envp, char *prefix, int quote)
{
	int		i;

	i = -1;
	while (envp && envp[++i])
		if (print_variable(envp[i], prefix, quote) < 0)
			return (BUILTIN_ERR_CODE);
	return (0);
}
