/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_predicate3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:54:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 11:23:32 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_builtins[] = {"echo", "cd", "pwd", "export", "unset",
	"env", "exit", NULL};

bool	is_str_redirection(const char *str)
{
	return (is_str_great(str) || is_str_dgreat(str) || is_str_less(str));
}

bool	is_str_builtin(const char *str)
{
	int	i;

	i = 0;
	while (g_builtins[i])
	{
		if (strcmp(str, g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

bool	is_str_empty_quote(const char *str)
{
	return (ft_strcmp(str, "\'\'") == 0 || ft_strcmp(str, "\"\"") == 0);
}

bool	is_str_enclosed_quote(const char *str)
{
	return (ft_strchr("\'\"", str[0]) && str[0] == str[ft_strlen(str) - 1]);
}