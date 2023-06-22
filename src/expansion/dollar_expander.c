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

static char	*get_key(char *line)
{
	char	*end;

	end = strfind(line, '=');
	if (!end)
		return (NULL);
	*end = '\0';
	return (line);
}

static char	*get_value(char *line)
{
	return (strfind(line, '=') + 1);
}

static char	*expand_word(char *word, char **envp)
{
	char	*tmp_var;

	while (envp && *envp)
	{
		if (!ft_strcmp(word, get_key(*envp)))
			return (get_value(*envp));
		envp++;
	}
	return (word);
}

/*	expands a full string (ie. hd data)	*/
char	*expand_dollar(char *str, char **envp)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ()
	}	
}
