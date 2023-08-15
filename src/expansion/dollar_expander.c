/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 15:02:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// gerer sans erreur les cas ou envp est null (env -i ./minishell)

/*	wd, wd_end and ret no need to be protected (cf. notion)	*/
char	*get_next_word_expanded(char **ret, char *str, char **envp, int status)
{
	char	*word_end;
	char	*last_status;

	if (*str == '$' && *(str + 1) == '?')
	{
		last_status = ft_itoa(status);
		*ret = strjoin2(*ret, last_status);
		return (str + 2);
	}
	word_end = strfind_if(str + 1, &is_c_end_envar);
	if (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_'))
		*ret = strjoin2(*ret, expand_wd(extract_wd(str, word_end), envp));
	else
		get_next_word_not_expanded(ret, str, word_end);
	return (word_end);
}

char	*get_next_word_not_expanded(char **ret, char *str, char *word_end)
{
	*ret = strjoin2(*ret, extract_wd(str, word_end));
	return (word_end);
}

/*	apply on all WORD except : here_doc lim + already expanded WORD	*/
char	*expand_dollar(char *str, char **envp, int status)
{
	char	*tmp;
	char	*ret;
	char	*next_s_quote;
	int		is_under_d_quote;

	is_under_d_quote = -1;
	tmp = str;
	ret = ft_strdup("");
	if (!ret || !tmp)
		return (free(ret), NULL);
	while (*tmp)
	{
		if (*tmp == D_QUOTE)
			is_under_d_quote *= -1;
		next_s_quote = ft_strchr(tmp + 1, S_QUOTE);
		if (is_under_d_quote < 0 && *tmp == S_QUOTE && next_s_quote)
			tmp = get_next_word_not_expanded(&ret, tmp, next_s_quote + 1);
		else
			tmp = get_next_word_expanded(&ret, tmp, envp, status);
		if (!tmp || !ret)
			return (free(ret), NULL);
	}
	return (ret);
}

/*	quoted stuff are expanded + str cant be null (cf. launch hd)	*/
char	*expand_dollar_here_doc(char *str, char **envp, int status)
{
	char	*tmp;
	char	*ret;

	tmp = str;
	ret = ft_strdup("");
	if (!ret)
		return (free(str), free(ret), NULL);
	while (*tmp)
	{
		tmp = get_next_word_expanded(&ret, tmp, envp, status);
		if (!tmp || !ret)
			return (free(str), free(ret), NULL);
	}
	return (free(str), ret);
}

/*	search forbidden blank in $var of redirfilename
	$var can have blank if underquote : "$var" ok ; var="\" \"" ko	*/
int	check_amb_redir(char *str, char **envp)
{
	char	*word;

	while (str && *str)
	{
		if (str && *str == D_QUOTE)
			str = ft_strchr(str + 1, D_QUOTE) + 1;
		if (str && *str == S_QUOTE)
			str = ft_strchr(str + 1, S_QUOTE) + 1;
		else if (str && *str == '$')
		{
			word = expand_wd(extract_wd(str, strfind_if(str + 1, \
				&is_c_end_envar)), envp);
			if (!word)
				return (ALLOC_FAIL);
			if (is_there_a_blank(word) || !ft_strlen(word))
				return (free(word), FALSE);
			free(word);
			str = strfind_if(str + 1, &is_c_end_envar);
		}
		else if (str && *str)
			str = strfind_if(str + 1, &is_c_end_envar) + 1;
	}
	return (TRUE);
}
