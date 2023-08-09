/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:42:56 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/09 16:35:29 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

/* builtin (ret 1) or execve (ret 0)	*/
int	check_cd(char **args)
{
	int	i;
	int	argc;

	argc = 0;
	i = 0;
	while (args && args[i])
	{
		argc++;
		i++;
	}
	if (argc != 2)
		return (0);
	if (args[1][0] == '-')
		return (0);
	return (1);
}

int	cd_error(char *path)
{
	char		*msg;
	const char	*prefix = "minishell: cd: ";

	msg = ft_strjoin(prefix, path);
	if (!msg)
		return (ALLOC_FAIL);
	perror(msg);
	free(msg);
	return (0);
}

int	cd(char *path, char **envp)
{
	int		chdir_status;
	char	*export_args[3];

	chdir_status = chdir(path);
	if (!chdir_status)
	{
		export_args[0] = "export";
		export_args[1] = strjoin3("OLDPWD", "=", get_envalue("PWD", envp));
		export_args[2] = NULL;
		if (export(export_args, &envp) == ALLOC_FAIL)
			return (free(export_args[1]), ALLOC_FAIL);
		free(export_args[1]);
		export_args[0] = "export";
		export_args[1] = strjoin3("PWD", "=", getcwd(NULL, 0));
		export_args[2] = NULL;
		if (export(export_args, &envp) == ALLOC_FAIL)
			return (free(export_args[1]), ALLOC_FAIL);
		free(export_args[1]);
	}
	else
		if (cd_error(path) == ALLOC_FAIL)
			return (ALLOC_FAIL);
	return (chdir_status * -1);
}
