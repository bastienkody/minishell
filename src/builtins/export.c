/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:43:29 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/10 20:34:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* builtin ret 1, execve ret 0	*/
int	check_export(char **args)
{
	if (args[1] && args[1][0] == '-' && ft_strlen(args[1]) > 1)
		return (0);
	return (1);
}

int	args_to_key_value(char **key_value, char *args)
{
	if (key_value[0])
		free(key_value[0]);
	if (key_value[1])
		free(key_value[1]);
	if (ft_strchr(args, '='))
	{
		key_value[0] = get_key_2(args);
		key_value[1] = ft_strdup(get_value(args));
	}
	else
	{
		key_value[0] = ft_strdup(args);
		key_value[1] = ft_strdup("");
	}
	return ((key_value[0] != NULL && key_value[1] != NULL));
}

int	is_key_valid(char *key, char *line)
{
	const char	*bad_char = ",.:!?~*^%$#@[]{}+-/\\";

	if (ft_strlen(key) == 0 || (*key != 95 && !ft_isalpha(*key)))
		return (err_builtin("export", line, ERR_ID_EXPORT), 0);
	while (*key)
	{
		if (ft_strchr(bad_char, *key))
			if (!(*key == '+' && *(key + 1) == '\0'))
				return (err_builtin("export", line, ERR_ID_EXPORT), 0);
		key++;
	}
	return (1);
}

int	export_each(char *key_value[3], char *entry, char ***envp)
{
	char	*key;

	key = ft_strdup(key_value[0]);
	if (!key)
		return (ALLOC_FAIL);
	if (ft_strchr(key, '+'))
		key[ft_strlen(key) - 1] = '\0';
	if (is_var_set(key, *envp) == 1 && ft_strchr(entry, '='))
	{
		if (ft_strchr(key_value[0], '+'))
		{
			if (concat_envar(key_value[0], key_value[1], *envp) == ALLOC_FAIL)
				return (free_char_matrix(key_value), free(key), ALLOC_FAIL);
		}
		else if (mod_envar(key_value[0], key_value[1], *envp) == ALLOC_FAIL)
			return (free_char_matrix(key_value), free(key), ALLOC_FAIL);
	}
	else if (is_var_set(key, *envp) == 0 && ft_strchr(entry, '='))
	{
		if (add_envar(key_value[0], key_value[1], envp) == ALLOC_FAIL)
			return (free_char_matrix(key_value), free(key), ALLOC_FAIL);
	}
	else if (is_var_set(key, *envp) == ALLOC_FAIL)
		return (free_char_matrix(key_value), free(key), ALLOC_FAIL);
	return (free(key), TRUE);
}

int	export(char **args, char ***envp)
{
	int		ret;
	char	**sorted;
	char	*key_value[3];

	if (!args[1])
	{
		sorted = charmatrix_buble_sort(*envp);
		if (!sorted)
			return (ALLOC_FAIL);
		return (env(sorted, PREFIX_EXPORT, 1), free_char_matrix(sorted), 0);
	}
	ret = 0;
	key_value[0] = NULL;
	key_value[1] = NULL;
	key_value[2] = NULL;
	while (*(++args))
	{
		if (args_to_key_value(key_value, *args) == 0)
			return (free(key_value[0]), free(key_value[1]), ALLOC_FAIL);
		if (is_key_valid(key_value[0], *args) == 0)
			ret = 1;
		else if (export_each(key_value, *args, envp) == ALLOC_FAIL)
			return (free(key_value[0]), free(key_value[1]), ALLOC_FAIL);
	}
	return (free(key_value[0]), free(key_value[1]), ret);
}
