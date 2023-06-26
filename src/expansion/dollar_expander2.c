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

/*	append expanded word to ret ; returns actualized str	
	wd, wd_end and ret no need to be protected (cf. notion)	*/
char	*get_next_word_expanded(char **ret, char *str, char **envp)
{
	char	*word;
	char	*word_end;

	word_end = str + 1; 
	if (is_c_dollar(*str))
	{
		word_end = strfind_if(str + 1, &is_c_blank_nl_dollar);
		word = expand_wd(extract_wd(str, word_end), envp);
		*ret = strjoin(*ret, word);
		free(word);
	}
	else
		*ret = str_one_char_join(*ret, *str);
	return (word_end);
}

/*	only dollar + quoted stuff are expanded	
	input str cannot be null (cf. launch hd)	*/
char	*expand_here_doc(char *str, char **envp)
{
	char	*tmp;
	char	*ret;

	tmp = str;
	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	while (*tmp)
	{
		tmp = get_next_word_expanded(&ret, tmp, envp);
		if (!tmp || !ret)
			return (NULL);
	}
	return (free(str), ret);
}
