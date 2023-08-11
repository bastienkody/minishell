/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_basics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:08:34 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/01 17:37:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_envalue(char *key, char **envp)
{
	char	*key_comp;

	while (envp && *envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (NULL);
		if (!ft_strcmp(key, key_comp))
			return (free(key_comp), ft_strdup(get_value(*envp)));
		free(key_comp);
		envp++;
	}
	return (ft_strdup(""));
}

int	add_envar(char *key, char *value, char ***envp)
{
	char	*env_line;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, value);
	if (!env_line)
		return (ALLOC_FAIL);
	*envp = charmatrix_add_one(*envp, env_line);
	if (!*envp)
		return (ALLOC_FAIL);
	return (1);
}

int	supp_envar(char *key, char ***envp)
{
	*envp = charmatrix_del_one(*envp, key);
	if (!*envp)
		return (ALLOC_FAIL);
	return (1);
}

int	mod_envar(char *key, char *new_value, char **envp)
{
	char	*env_line;
	char	*key_comp;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, new_value);
	if (!env_line)
		return (ALLOC_FAIL);
	while (envp && *envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (ALLOC_FAIL);
		if (!ft_strcmp(key, key_comp))
		{
			free(*envp);
			*envp = env_line;
			return (free(key_comp), 1);
		}
		free(key_comp);
		envp++;
	}
	return (0);
}

int	is_var_set(char *key, char **envp)
{
	char	*key_comp;

	if (!key || !envp)
		return (0);
	while (*envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (ALLOC_FAIL);
		if (!ft_strcmp(key, key_comp))
			return (free(key_comp), 1);
		free(key_comp);
		envp++;
	}
	return (0);
}
