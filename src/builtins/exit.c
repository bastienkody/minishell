/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 14:43:21 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	si premier argument str : exit + code 1 + numeric arg required	
	si premier arg est nb:
		si seul arg : exit atoi_127(arg)
		si poly arg : do not exit + too many arg + code 2
	si pas d'arg : exit last status
*/

int	check_exit(char **args)
{
	if (args[1] && args[1][0] == '-')
		return (0);
	return (1);
}

int	exit_blt(char **args, char **envp, void *truc)
{
	(void)args;
	(void)envp;
	(void)truc;
	return (0);
}
