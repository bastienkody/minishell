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

/*	envp is fucked : '=' de *envp is replaced by \0 so only keys in envp	*/
char	*get_key(char *line)
{
	char	*end;

	end = strfind(line, '=');
	if (!end)
		return (NULL);
	*end = '\0';
	return (line);
}

/* malloc to avoid fucking up envp 	*/
char	*get_key_2(char *line)
{
	char	*end;
	char	*ret;

	ret = ft_strdup(line);
	if (!ret)
		return (NULL);
	end = strfind(ret, '=');
	if (end)
		*end = '\0';
	return (ret);
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
	char	*key_comp;

	if (!word)
		return (NULL);
	while (envp && *envp)
	{
		key_comp = get_key_2(*envp);
		if (!key_comp)
			return (free(word), NULL);
		if (!ft_strcmp(word + sizeof(char), key_comp))
			return (free(word), free(key_comp), ft_strdup(get_value(*envp)));
		envp++;
		free(key_comp);
	}
	return (free(word), ft_strdup(""));
}
