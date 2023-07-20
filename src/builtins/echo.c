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
int	check_echo(char **argv)
{
	++argv;
	if (argv && *argv && **argv == '-')
	{
		if (ft_strchr(*argv, 'e') || ft_strchr(*argv, 'E'))
			if (is_only_e_e_n(*argv))
				return (0);
	}
	return (1);
}

int	echo(char **argv)
{
	int			trailing_nl;
	const char	sep[2] = {'\n', ' '};

	argv++;
	trailing_nl = 1;
	if (argv && *argv && !ft_strncmp("-n", *argv, 2) && is_only_n(*argv))
	{
		trailing_nl = 0;
		argv++;
	}
	while (argv && *argv)
	{
		if (write(1, *argv, ft_strlen(*argv)) < 0)
			return (-1);
		if (*(argv + 1) && write(1, &sep[1], 1) < 0)
			return (-1);
		argv++;
	}
	if (trailing_nl)
		return (write(1, &sep[0], 1) < 0);
	return (0);
}
