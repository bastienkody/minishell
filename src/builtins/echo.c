/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:12 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/12 17:50:08 by aguyon           ###   ########.fr       */
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

int	check_echo(char **args)
{
	++args;
	while (args && *args && **args == '-')
	{
		if (ft_strchr(*args, 'e') || ft_strchr(*args, 'E'))
			if (is_only_e_e_n(*args))
				return (0);
		args++;
	}
	return (1);
}

int	echo(char **args)
{
	int			trailing_nl;
	const char	sep[2] = {'\n', ' '};

	args++;
	trailing_nl = 1;
	while (args && *args && !ft_strncmp("-n", *args, 2) && is_only_n(*args))
	{
		trailing_nl = 0;
		args++;
	}
	while (args && *args)
	{
		if (!is_str_empty_quote(*args))
			if (write(1, *args, ft_strlen(*args)) < 0)
				return (BUILTIN_ERR_CODE);
		if (*(args + 1) && write(1, &sep[1], 1) < 0)
			return (BUILTIN_ERR_CODE);
		args++;
	}
	if (trailing_nl)
		if (write(1, &sep[0], 1) < 0)
			return (BUILTIN_ERR_CODE);
	return (0);
}
