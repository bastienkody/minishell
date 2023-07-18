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

char	*get_envalue(char *key, char **envp)
{
	while (envp && *envp)
	{
		if (!ft_strcmp(key, get_key(*envp)))
			return (get_value(*envp));
		envp++;
	}
	return (NULL);
}

int	mod_envar(char *key, char *new_value, char **envp)
{
	char	*new_env_line;
	char	*env_line;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, new_value);
	if (!env_line)
		return (MALLOC_FAIL_REDIR);
	while (envp && *envp)
	{
		if (!ft_strcmp(key, get_key(*envp)))
		{
			free(*envp);
			*envp = env_line;
			return (1);
		}
		envp++;
	}
	return (0);
}

int	cd(char *path, char **envp)
{
	int		i;
	int		chdir_status;

	chdir_status = chdir(path);
	if (!chdir_status && envp)
	{
		if (mod_envar("OLD_PWD", get_envalue("PWD", envp), envp) == MALLOC_FAIL_REDIR)
			return (MALLOC_FAIL_REDIR);
		if (mod_envar("PWD", getcwd(NULL, 0), envp) == MALLOC_FAIL_REDIR)
			return (MALLOC_FAIL_REDIR);
	}
	return (chdir_status);
}
