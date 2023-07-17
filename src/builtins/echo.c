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

int	echo(char **argv)
{
	int		trailing_nl;
	char	nl;

	nl = '\n';
	trailing_nl = 1;
	if (argv && *argv && !ft_strcmp("-n", *argv) && ft_strlen(*argv) == 2)
	{
		trailing_nl = 0;
		argv++;
	}
	while (argv && *argv)
	{
		if (write(1, *argv, ft_strlen(*argv)) < 0)
			return (-1);
		if (trailing_nl)
			if (write(1, &nl, 1) < 0)
				return (-1);
		argv++;
	}
	return (0);
}
