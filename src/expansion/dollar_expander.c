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

/*	input word is malloced but returns a stacked str	*/
char	*expand_wd(char *word, char **envp)
{
	if (!word)
		return (NULL);
	while (envp && *envp)
	{
		if (!ft_strcmp(word, get_key(*envp)))
			return (free(word), get_value(*envp));
		envp++;
	}
	return (free(word), "");
}

/*	only dollar + quoted stuff are expanded	*/
char	*expand_here_doc(char *str, char **envp)
{
	int		i;
	char	*ret;
	char	*word;
	char	*word_end;

	i = -1;
	ret = NULL;
	while (str[++i])
	{
		if (is_c_dollar(str[i]))
		{
			word_end = strfind_if(str + i, &is_c_blank_or_dollar);
			word = expand_wd(extract_wd(str+i, word_end), envp);
			ret = ft_realloc(ret, ft_strlen(ret) + ft_strlen(word) * sizeof(char));
			if (!ret)
				return (NULL);
			ft_memcpy(&ret[ft_strlen(ret)], word, ft_strlen(word));
			while (&str[i] != word_end)
				i++;
		}
		else
			ret = str_one_char_join(ret, str[i]);
		if (!ret)
			return (NULL);
	}
	return (free(str), ret);
}
