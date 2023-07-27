/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/27 14:56:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// gerer sans erreur les cas ou envp est null (env -i ./minishell)

/*	wd, wd_end and ret no need to be protected (cf. notion)	*/
char	*get_next_word_expanded(char **ret, char *str, char **envp, int last_status)
{
	char	*word_end;
	char	*last_stratus;

	last_status = LAST_RETURN_STATUS; // to be suppressed when main has last_status
	if (*str == '$' && *(str + 1) == '?')
	{
		last_stratus = ft_itoa(last_status);
		*ret = strjoin2(*ret, last_stratus);
		return (free(last_stratus), str + 2);
	}
	word_end = strfind_if(str + 1, &is_c_blank_nl_dollar_s_d_quote);
	if (*str == '$')
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
char	*expand_dollar(char *str, char **envp, int last_status)
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
			tmp = get_next_word_expanded(&ret, tmp, envp, last_status);
		if (!tmp || !ret)
			return (free(ret), NULL);
		// double free possible on tmp (str) when freeing the tree?
	}
	return (ret);
}

/*	quoted stuff are expanded + str cant be null (cf. launch hd)	*/
char	*expand_dollar_here_doc(char *str, char **envp, int last_status)
{
	char	*tmp;
	char	*ret;

	tmp = str;
	ret = ft_strdup("");
	if (!ret)
		return (free(str), free(ret), NULL);
	while (*tmp)
	{
		tmp = get_next_word_expanded(&ret, tmp, envp, last_status);
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
		if (*str == D_QUOTE)
			str = ft_strchr(str + 1, D_QUOTE) + 1;
		if (*str == S_QUOTE)
			str = ft_strchr(str + 1, S_QUOTE) + 1;
		else if (*str == '$')
		{
			word = expand_wd(extract_wd(str, strfind_if(str + 1, \
				&is_c_blank_nl_dollar_s_d_quote)), envp);
			if (!word)
				return (MALLOC_FAIL);
			if (is_there_a_blank(word) || !ft_strlen(word))
				return (free(word), FALSE);
			free(word);
			str = strfind_if(str + 1, &is_c_blank_nl_dollar_s_d_quote);
		}
		else
			str = strfind_if(str + 1, &is_c_blank_nl_dollar_s_d_quote);
	}
	return (TRUE);
}
