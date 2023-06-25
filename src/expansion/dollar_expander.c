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

/*	append expanded word to ret ; returns word_end
	deref_ret because (&(&tab[i])) not legal ...	*/
char	*get_next_word_expanded(char **ret, char *str, char **envp)
{
	char	*word;
	char	*word_end;
	char	*deref_ret;

	word_end = strfind_if(str, &is_c_blank_or_dollar);
	word = expand_wd(extract_wd(str, word_end), envp);
	*ret = ft_realloc(*ret, (ft_strlen(*ret) + ft_strlen(word)) * sizeof(char));
	if (!*ret)
		return (NULL);
	deref_ret = *ret;
	ft_memcpy(&deref_ret[ft_strlen(*ret)], word, ft_strlen(word));
	return (word_end);
}

/*	only dollar + quoted stuff are expanded	*/
char	*expand_here_doc(char *str, char **envp)
{
	int		i;
	char	*ret;
	char	*word_end;

	i = -1;
	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (is_c_dollar(str[i]))
		{
			word_end = get_next_word_expanded(&ret, str + i, envp);
			if (!word_end)
				return (NULL);
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
