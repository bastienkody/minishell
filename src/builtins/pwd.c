/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:43 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 14:43:45 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_pwd(char **args)
{
	if (args[1] && args[1][0] == '-' && ft_strlen(args[1]) > 1)
		return (0);
	return (1);
}

int	pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (!str)
		return (-1);
	ft_fprintf(1, "%s\n", str);
	free(str);
	return (0);
}
