/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:39 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_envalue(char *key, char **envp)
{
	char	*key_comp;

	while (envp && *envp)
	{
		//ft_fprintf(1, "key(%s)envp:%s\n", key, *envp);
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

int	add_envar(char *key, char *value, char ***envp)
{
	char	*env_line;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, value);
	if (!env_line)
		return (MALLOC_FAIL);
	*envp = charmatrix_add_one(*envp, env_line);
	if (!*envp)
		return (MALLOC_FAIL);
	return (1);
}

int	supp_envar(char *key, char ***envp)
{
	*envp = charmatrix_del_one(*envp, key);
	if (!*envp)
		return (MALLOC_FAIL);
	return (1);
}

int	mod_envar(char *key, char *new_value, char **envp)
{
	char	*env_line;
	char	*key_comp;

	env_line = ft_strjoin(key, "=");
	env_line = strjoin(env_line, new_value);
	if (!env_line)
		return (MALLOC_FAIL);
	while (envp && *envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (MALLOC_FAIL);
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

int	is_var_set(char *key, char **envp)
{
	char	*key_comp;

	if (!key || !envp)
		return (0);
	while (*envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (MALLOC_FAIL);
		if (!ft_strcmp(key, key_comp))
			return (free(key_comp), 1);
		free(key_comp);
		envp++;
	}
	return (0);
}
