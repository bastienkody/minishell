/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:08:11 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/29 17:21:31 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	_len_delim(const char *str)
{
	size_t		len;

	if (!ft_strchr(" \t", *str) && ft_strchr("<>&|", *str))
	{
		len = 1;
		if (*str == *(str + 1))
			len++;
	}
	else
		len = strfind_not(str, *str) - str;
	return (len);
}

static size_t	_word_len(const char *str)
{
	size_t	len;
	int		is_inside_quote;
	char	quote;

	len = 0;
	is_inside_quote = 0;
	quote = '\0';
	while (*str != '\0' && ft_strchr(DELIM, *str) == NULL)
	{
		if (ft_strchr("\"\'", *str) && is_inside_quote && *str == quote)
		{
			is_inside_quote = 0;
			quote = '\0';
		}
		else if (ft_strchr("\"\'", *str) && !is_inside_quote)
		{
			is_inside_quote = 1;
			quote = *str;
		}
		len++;
		str++;
	}
	return (len);
}

static size_t	_substr_len(const char *str)
{
	size_t	len;

	if (ft_strchr("()", *str) != NULL)
		len = 1;
	else if (ft_strchr(DELIM, *str))
		len = _len_delim(str);
	else
		len = _word_len(str);
	return (len);
}

static char	*_get_next_token(const char **str)
{
	const size_t	len = _substr_len(*str);
	char			*token;

	token = ft_substr(*str, 0, len);
	*str += len;
	return (token);
}

t_llist	*lsttok(const char *str)
{
	t_llist	*llist;
	t_llist	*new;
	char	*token;

	llist = NULL;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		token = _get_next_token(&str);
		if (token == NULL)
			return (llstclear(&llist, free), NULL);
		new = llstnew(token);
		if (new == NULL)
			return (llstclear(&llist, free), NULL);
		llstadd_back(&llist, new);
	}
	return (llist);
}
