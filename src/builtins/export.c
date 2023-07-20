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
	const char	*bad_char = "=+-/\\";

	if (ft_strlen(key) == 0)
		return (err_builtin("export", line, ERR_ID_EXPORT), 0);
	while (*key)
	{
		if (ft_strchr(bad_char, *key))
			return (err_builtin("export", line, ERR_ID_EXPORT), 0);
		key++;
	}
	return (1);
}

int	export_each(char *key_value[2], char *entry, char ***envp)
{
	if (is_var_set(key_value[0], *envp) == 1 && ft_strchr(entry, '='))
	{
		if (mod_envar(key_value[0], key_value[1], *envp) == MALLOC_FAIL)
			return (free(key_value[0]), free(key_value[1]), MALLOC_FAIL);
	}
	else if (is_var_set(key_value[0], *envp) == 0 && ft_strchr(entry, '='))
	{
		if (add_envar(key_value[0], key_value[1], envp) == MALLOC_FAIL)
			return (free(key_value[0]), free(key_value[1]), MALLOC_FAIL);
	}
	else if (is_var_set(key_value[0], *envp) == MALLOC_FAIL)
		return (free(key_value[0]), free(key_value[1]), MALLOC_FAIL);
	return (TRUE);
}

int	export(char **args, char ***envp)
{
	int		ret;
	char	*key_value[2];

	if (!args[1])
		return (print_env(*envp, PREFIX_EXPORT), 0);
	ret = 0;
	key_value[0] = NULL;
	key_value[1] = NULL;
	while (*(++args))
	{
		if (args_to_key_value(key_value, *args) == 0)
			return (free(key_value[0]), free(key_value[1]), MALLOC_FAIL);
		if (is_key_valid(key_value[0], *args) == 0)
		{
			ret = 1;
			continue;
		}
		if (export_each(key_value, *args, envp) == MALLOC_FAIL)
			return (free(key_value[0]), free(key_value[1]), MALLOC_FAIL);
	}
	return (free(key_value[0]), free(key_value[1]), ret);
}
