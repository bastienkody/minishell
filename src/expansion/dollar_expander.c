/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/23 14:13:53 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// gerer sans erreur les cas ou envp est null (env -i ./minishell)

// char	*get_end_var(const char *str)
// {
// 	if (ft_isdigit(*str))
// 		return ((char *)(str + 1));
// 	while (*str != '\0' && (ft_isalnum(*str) || *str == '_'))
// 		str++;
// 	return ((char *)str);

// }

/*	wd, wd_end and ret no need to be protected (cf. notion)	*/
// char	*get_next_word_expanded(char **ret, char *str, char **envp, int status)
// {
// 	char	*word_end;
// 	char	*last_status;

// 	if (*str == '$' && *(str + 1) == '?')
// 	{
// 		last_status = ft_itoa(status);
// 		*ret = strjoin2(*ret, last_status);
// 		return (str + 2);
// 	}
// 	word_end = get_end_var(str + 1);
// 	if (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_'))
// 		*ret = strjoin2(*ret, expand_wd(extract_wd(str, word_end), envp));
// 	else
// 	{
// 		if (str[0] != '\0' && (ft_isalnum(str[1] || str[1] == '_')))
// 			str++;
// 		get_next_word_not_expanded(ret, str, word_end);
// 	}
// 	return (word_end);
// }

// char	*get_next_word_not_expanded(char **ret, char *str, char *word_end)
// {
// 	*ret = strjoin2(*ret, extract_wd(str, word_end));
// 	return (word_end);
// }

/*	apply on all WORD except : here_doc lim + already expanded WORD	*/
// char	*expand_dollar(char *str, char **envp, int status)
// {
// 	char	*tmp;
// 	char	*ret;
// 	char	*next_s_quote;
// 	int		is_under_d_quote;

// 	is_under_d_quote = -1;
// 	tmp = str;
// 	ret = ft_strdup("");
// 	if (!ret || !tmp)
// 		return (free(ret), NULL);
// 	while (*tmp)
// 	{
// 		if (*tmp == D_QUOTE)
// 			is_under_d_quote *= -1;
// 		next_s_quote = ft_strchr(tmp + 1, S_QUOTE);
// 		if (is_under_d_quote < 0 && *tmp == S_QUOTE && next_s_quote)
// 			tmp = get_next_word_not_expanded(&ret, tmp, next_s_quote + 1);
// 		else
// 			tmp = get_next_word_expanded(&ret, tmp, envp, status);
// 		if (!tmp || !ret)
// 			return (free(ret), NULL);
// 	}
// 	return (ret);
// }

/*	quoted stuff are expanded + str cant be null (cf. launch hd)	*/
// char	*expand_dollar_here_doc(char *str, char **envp, int status)
// {
// 	char	*tmp;
// 	char	*ret;

// 	tmp = str;
// 	ret = ft_strdup("");
// 	if (!ret)
// 		return (free(str), free(ret), NULL);
// 	while (*tmp)
// 	{
// 		tmp = get_next_word_expanded(&ret, tmp, envp, status);
// 		if (!tmp || !ret)
// 			return (free(str), free(ret), NULL);
// 	}
// 	return (free(str), ret);
// }

// /*	search forbidden blank in $var of redirfilename
// 	$var can have blank if underquote : "$var" ok ; var="\" \"" ko	*/
// int	check_amb_redir(char *str, char **envp)
// {
// 	char	*word;

// 	while (str && *str)
// 	{
// 		if (str && *str == D_QUOTE)
// 			str = ft_strchr(str + 1, D_QUOTE) + 1;
// 		else if (str && *str == S_QUOTE)
// 			str = ft_strchr(str + 1, S_QUOTE) + 1;
// 		else if (str && *str == '$')
// 		{
// 			word = expand_wd(extract_wd(str, strfind_if(str + 1,
// 				&is_c_end_envar)), envp);
// 			if (!word)
// 				return (ALLOC_FAIL);
// 			if (is_there_a_blank(word) || !ft_strlen(word))
// 				return (free(word), FALSE);
// 			free(word);
// 			str = strfind_if(str + 1, &is_c_end_envar);
// 		}
// 		else if (str && *str)
// 			str = strfind_if(str + 1, &is_c_end_envar);
// 	}
// 	return (TRUE);
// }

size_t	get_identifier_len(const char *str)
{
	const char *begin = str;

	while (*str != '\0' && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (str - begin);
}

// char	*get_next(const char *str)
// {
// 	if (*str == '$')
// 	{
// 		str++;
// 		if (ft_isdigit(*str) || *str == '?')
// 			str++;
// 		else
// 			while (*str != '\0' && (ft_isalnum(*str) || *str == '_'))
// 				str++;
// 	}
// 	else
// 	{
// 		if (ft_strchr("\"\'", *str))
// 			str = ft_strchr(str + 1, *str) + 1;
// 		else
// 			while (*str != '\0' && !ft_strchr("\"\'$", *str))
// 				str++;
// 	}
// 	return ((char *)str);
// }

// char	*get_next_inside_dquote(const char *str)
// {
// 	if (*str++ == '$')
// 	{
// 		if (ft_isdigit(*str) || *str == '?')
// 			str++;
// 		else
// 			while (*str != '\"' && (ft_isalnum(*str) || *str == '_'))
// 				str++;
// 	}
// 	else
// 	{
// 		while (*str != '\"' && *str != '$')
// 			str++;
// 	}
// 	return ((char *)str);
// }

static	char *my_strjoin(char *s1, char *s2)
{
	char *const	temp = s1;
	char *const	res = ft_strjoin(s1, s2);

	return (free(temp), res);
}

bool	is_solo_dollar(char *str)
{
	if (str[0] != '$')
		return (false);
	if (str[1] == '\0')
		return (true);
	if (ft_isalnum(str[1]) || ft_strchr("?_", str[1]))
		return (false);
	if (ft_strchr("\'\"", str[1]) && str[2] != '\0')
		return (false);
	return (true);
}

char	*my_expand(char *str, char **envp, int status)
{
	char	*res;

	if (is_solo_dollar(str))
		return (ft_strdup("$"));
	if (str[1] == '?')
		return (ft_itoa(status));
	else if (ft_strchr("\"\'", str[1]))
		return (ft_strdup(""));
	str = ft_substr(str, 1, get_identifier_len(str + 1));
	if (str == NULL)
		return (NULL);
	res = expand_wd(str, envp);
	return (free(str), res);
}

// char	*expand_dollar_dquote(char *str, char **envp, int status)
// {
// 	char	*res;
// 	char	*temp;
// 	char	*next;

// 	res = ft_strdup("");
// 	while (*str != '\"')
// 	{
// 		next = get_next_inside_dquote(str);
// 		if (str[0] == '$' && (ft_isalnum(str[1]) || ft_strchr("_?", str[1])))
// 			temp = my_expand(str, envp, status);
// 		else
// 			temp = ft_substr(str, 0, next - str);
// 		if (temp == NULL)
// 			return (free(res), NULL);
// 		res = my_strjoin(res, temp);
// 		free(temp);
// 		if (res == NULL)
// 			return (NULL);
// 		str = next;
// 	}
// 	return (res);
// }

// char	*expand_dollar(char *str, char **envp, int status)
// {
// 	char			*res;
// 	char			*temp;
// 	char			*next;

// 	res = ft_strdup("");
// 	while (*str != '\0')
// 	{
// 		next = get_next(str);
// 		if (str[0] == '$' && (ft_isalnum(str[1]) || (str[1] && ft_strchr("\"\'_?", str[1]))))
// 			temp = my_expand(str, envp, status);
// 		else if (str[0] == '\'')
// 			temp = ft_substr(str, 1, next - str - 2);
// 		else if (str[0] == '\"')
// 			temp = expand_dollar_dquote(str + 1, envp, status);
// 		else
// 			temp = ft_substr(str, 0, next - str);
// 		if (temp == NULL)
// 			return (free(res), NULL);
// 		res = my_strjoin(res, temp);
// 		free(temp);
// 		if (res == NULL)
// 			return (NULL);
// 		str = next;
// 	}
// 	return (res);
// }

static char	*get_next(char *str, bool *is_inside_simple_quote, bool *is_inside_double_quote)
{
	if (str[0] == '$')
	{
		str++;
		if (str[0] == '?')
			return (str + 1);
		else
			while (*str != '\0' && (ft_isalnum(*str) || *str == '_'))
				str++;
	}
	else
	{
		while (*str)
		{
			if (*str == '\"' && !*is_inside_simple_quote)
				*is_inside_double_quote = !*is_inside_double_quote;
			else if (*str == '\'' && !*is_inside_double_quote)
				*is_inside_simple_quote = !*is_inside_simple_quote;
			if (*str == '$' && !*is_inside_simple_quote)
				return ((char *)str);
			else
				str++;
		}
	}
	return (str);
}

char	*expand_dollar(char *str, char **envp, int status)
{
	char	*res;
	char	*next;
	char	*temp;
	bool	is_inside_simple_quote;
	bool	is_inside_double_quote;

	res = ft_strdup("");
	is_inside_simple_quote = false;
	is_inside_double_quote = false;
	while (*str != '\0')
	{
		next = get_next(str, &is_inside_simple_quote, &is_inside_double_quote);
		if (str[0] == '$')
			temp = my_expand(str, envp, status);
		else
			temp = ft_substr(str, 0, next - str);
		if (temp == NULL)
			return (free(res), NULL);
		res = my_strjoin(res, temp);
		free(temp);
		if (res == NULL)
			return (NULL);
		str = next;
	}
	return (res);
}
