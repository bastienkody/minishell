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
		word_end = strfind_if(str + 1, &is_c_blank_nl_dollar_s_d_quote);
		word = expand_wd(extract_wd(str, word_end), envp);
		*ret = strjoin(*ret, word);
		free(word);
	}
	else
		*ret = str_one_char_join(*ret, *str);
	return (word_end);
}

/*	only dollar on not s_quoted stuff	
	input str can be null 	*/
char	*expand_dollar(char *str, char **envp)
{
	char	*tmp;
	char	*ret;
	char	*next_s_quote;

	tmp = str;
	ret = ft_strdup("");
	if (!ret || !tmp || !envp)
		return (free(ret), free(tmp), NULL);
	while (*tmp)
	{
		next_s_quote = ft_strchr(tmp + 1, S_QUOTE);
		if (*tmp == S_QUOTE && next_s_quote)
		{
			ret = strjoin2(ret, extract_wd(tmp, next_s_quote + 1));
			tmp = next_s_quote + 1;
		}
		else
			tmp = get_next_word_expanded(&ret, tmp, envp);
		if (!tmp || !ret)
			return (NULL);
	}
	return (free(str), ret);
}

/*	just appeler expand_d en checkant si ya un blank == amb redir?
	touch truc > yo$USER --> ok
	touch truc > "ca va" --> ok
	$A="yo yi" ; $B="\"yo yi\"" 
	touch truc >  $A --> ko
	touch truc >  $B --> ko (pas de lexing parsing ni expansion on expanded stuff)
	ccl :
	-si expansion = pas de blank (meme si quoted)
	-sans expansion = blank ok (obvs quoted if not it'd be several tokens)*/
char	*expand_dollar_redir_file(char *str)
{
	if (!str)
		return (NULL);
	return (str);
}

/*	only dollar + quoted stuff are expanded	
	str cant be null (cf. launch hd)	*/
char	*expand_dollar_here_doc(char *str, char **envp)
{
	char	*tmp;
	char	*ret;

	tmp = str;
	ret = ft_strdup("");
	if (!ret || !envp)
		return (free(ret), NULL);
	while (*tmp)
	{
		tmp = get_next_word_expanded(&ret, tmp, envp);
		if (!tmp || !ret)
			return (NULL);
	}
	return (free(str), ret);
}

/*	no quote rm on here_doc data	*/
char	*rm_peer_s_quotes(char *str)
{
	if (!str)
		return (NULL);
	
	return (str);
}