/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/24 12:00:09 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	get_identifier_len(const char *str)
{
	const char	*begin = str;

	while (*str != '\0' && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (str - begin);
}

// static char	*my_strjoin(char *s1, char *s2)
// {
// 	char *const	temp = s1;
// 	char *const	res = ft_strjoin(s1, s2);

// 	return (free(temp), res);
// }

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

static char	*get_next(char *str, bool *is_inside_simple_quote,
	bool *is_inside_double_quote)
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
		res = strjoin(res, temp);
		free(temp);
		if (res == NULL)
			return (NULL);
		str = next;
	}
	return (res);
}
