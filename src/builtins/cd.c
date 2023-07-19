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
	char	*key_comp;

	while (envp && *envp)
	{
		ft_fprintf(1, "key(%s)envp:%s\n", key, *envp);
		key_comp = get_key_2(*envp);	
		if (!key_comp)
			return (NULL);
		if (!ft_strcmp(key, key_comp))
			return (free(key_comp), ft_strdup(get_value(*envp)));
		free(key_comp);
		envp++;
	}
	return (ft_strdup("")); // not a malloc error .. 
}

int	mod_envar(char *key, char *new_value, char **envp)
{
	char	*env_line;
	char	*key_comp;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, new_value);
	if (!env_line)
		return (MALLOC_FAIL_REDIR);
	while (envp && *envp)
	{
		ft_fprintf(1, "key(%s)key_cmp(%s)New_value:(%s)*envp(%s)\n", key, key_comp, new_value, *envp);
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (MALLOC_FAIL_REDIR);
		if (!ft_strcmp(key, key_comp))
		{
			free(*envp);
			*envp = env_line;
			ft_fprintf(1, "entrey modified:%s\n", env_line);
			return (free(key_comp), 1);
		}
		free(key_comp);
		envp++;
	}
	return (0);
}

int	cd(char *path, char **envp)
{
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
