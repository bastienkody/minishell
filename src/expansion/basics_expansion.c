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

char	*get_key(char *line)
{
	char	*end;

	end = strfind(line, '=');
	if (!end)
		return (NULL);
	*end = '\0';
	return (line);
}

char	*get_value(char *line)
{
	return (strfind(line, '=') + 1);
}

/*	end excluded	*/
char	*extract_wd(char *start, char *end)
{
	char	*word;
	int		len;

	len = end - start;
	if (len <= 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	word[len--] = '\0';
	while (--end >= start)
		word[len--] = *end;
	return (word);
}

/*	word is malloced and word[0] == '$'	*/
char	*expand_wd(char *word, char **envp)
{
	if (!word)
		return (NULL);
	while (envp && *envp)
	{
		if (!ft_strcmp(word + sizeof(char), get_key(*envp)))
			return (free(word), ft_strdup(get_value(*envp)));
		envp++;
	}
	return (free(word), ft_strdup(""));
}

int	check_amb_redir(char *str)
{
	
}
