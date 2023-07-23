/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 11:50:46 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_only_e_e_n(char *str)
{
	const char	*accepted_char = "eEn";

	if (str)
	{
		str++;
		while (*str)
		{
			if (!ft_strchr(accepted_char, *str))
				return (0);
			str++;
		}
	}
	return (1);
}

int	is_only_n(char *str)
{
	if (str)
	{
		str++;
		while (*str)
		{
			if (*str != 'n')
				return (0);
			str++;
		}
	}
	return (1);
}

/* Use of builtin (1) or execve (0)	*/
int	check_echo(char **args)
{
	++args;
	if (args && *args && **args == '-')
	{
		if (ft_strchr(*args, 'e') || ft_strchr(*args, 'E'))
			if (is_only_e_e_n(*args))
				return (0);
	}
	return (1);
}

int	echo(char **args)
{
	int			trailing_nl;
	const char	sep[2] = {'\n', ' '};

	args++;
	trailing_nl = 1;
	if (args && *args && !ft_strncmp("-n", *args, 2) && is_only_n(*args))
	{
		trailing_nl = 0;
		args++;
	}
	while (args && *args)
	{
		if (write(1, *args, ft_strlen(*args)) < 0)
			return (-1);
		if (*(args + 1) && write(1, &sep[1], 1) < 0)
			return (-1);
		args++;
	}
	if (trailing_nl)
		return (write(1, &sep[0], 1) < 0);
	return (0);
}
