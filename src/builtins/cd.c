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
	(void)args;
	return (1);
}

int	cd_error_display(char *path)
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

int	mod_pwd_oldpwd(char ***envp)
{
	char	*export_args[3];

	export_args[0] = "export";
	export_args[1] = strjoin3("OLDPWD", "=", get_envalue("PWD", *envp));
	export_args[2] = NULL;
	if (export(export_args, envp) == ALLOC_FAIL)
		return (free(export_args[1]), ALLOC_FAIL);
	free(export_args[1]);
	export_args[0] = "export";
	export_args[1] = strjoin3("PWD", "=", getcwd(NULL, 0));
	export_args[2] = NULL;
	if (export(export_args, envp) == ALLOC_FAIL)
		return (free(export_args[1]), ALLOC_FAIL);
	free(export_args[1]);
	return (1);
}

int	cd(char **args, char **envp)
{
	int		chdir_status;

	if (!args[1])
		return (err_msg(args[0], "Please provide an argument"), 1);
	if (args[2])
		return (err_msg(args[0], ERR_TMA), 1);
	chdir_status = chdir(args[1]);
	if (!chdir_status)
	{
		if (mod_pwd_oldpwd(&envp) == ALLOC_FAIL)
			return (ALLOC_FAIL);
	}
	else
		if (cd_error_display(args[1]) == ALLOC_FAIL)
			return (ALLOC_FAIL);
	return (chdir_status * -1);
}
