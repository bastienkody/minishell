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

/*	wd, wd_end and ret no need to be protected (cf. notion)	*/
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

char	*get_next_word_not_expanded(char **ret, char *str, char *word_end)
{
	*ret = strjoin2(*ret, extract_wd(str, word_end));
	return (word_end);
}

char	*expand_dollar(char *str, char **envp)
{
	char	*tmp;
	char	*ret;
	char	*next_s_quote;
	int		is_under_d_quote;

	is_under_d_quote = -1;
	tmp = str;
	ret = ft_strdup("");
	if (!ret || !tmp || !envp)
		return (free(ret), free(tmp), NULL);
	while (*tmp)
	{
		if (is_c_d_quote(*tmp))
			is_under_d_quote *= -1;
		next_s_quote = ft_strchr(tmp + 1, S_QUOTE);
		if (is_under_d_quote < 0 && *tmp == S_QUOTE && next_s_quote)
			tmp = get_next_word_not_expanded(&ret, tmp, next_s_quote + 1);
		else
			tmp = get_next_word_expanded(&ret, tmp, envp);
		if (!tmp || !ret)
			return (NULL);
	}
	return (free(str), ret);
}

/*	quoted stuff are expanded + str cant be null (cf. launch hd)	*/
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

/*	touch truc > yo$USER --> ok
	touch truc > "ca va" --> ok
	$A="yo yi" ; $B="\"yo yi\"" 
	touch truc >  $A --> ko
	touch truc >  $B --> ko (pas de lexing parsing ni expansion on expanded stuff)
	touch truc >  "$B" --> ok (single word)
	touch truc >  "yo $USER" --> ok (single word)
	ccl :
	- le redir file doit etre un single WORD apres expansion
	- si quote : blank acceptables
	- si pas quote : aucun blank (peu importe si expand ou pas)	*/
char	*expand_dollar_redir_file(char *str, char **envp)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strdup(str);
	if (!str || !tmp)
		return (free(str), NULL);
	ret = expand_dollar(tmp, envp);
	if (!ret)
		return (free(str), NULL);
	if (!is_str_quote_enclosed(ret) && is_there_a_blank(ret))
		return (err_msg(str, ERR_AMB_REDIR), free(str), free(ret), NULL);
	return (free(str), ret);
}
