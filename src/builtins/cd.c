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

/* builtin (ret 1) or execve (ret 0)	*/
int	check_cd(char **args)
{
	int	argc;

	while (args && *args)
	{
		argc++;
		args++;
	}
	if (argc != 2)
		return (0);
	if (args[1][0] == '-')
		return (0);
	return (1);
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
		if (export(export_args, &envp) == MALLOC_FAIL)
			return (free(export_args[1]), MALLOC_FAIL);
		free(export_args[1]);
		export_args[0] = "export";
		export_args[1] = strjoin3("PWD", "=", getcwd(NULL, 0));
		export_args[2] = NULL;
		if (export(export_args, &envp) == MALLOC_FAIL)
			return (free(export_args[1]), MALLOC_FAIL);
		free(export_args[1]);
	}
	return (chdir_status);
}
