/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:08:11 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/16 14:22:31 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	_substr_len(const char *str)
{
	size_t	len;

	if (ft_strchr("()", *str) != NULL)
		len = 1;
	else if (ft_strchr(DELIM, *str))
		len = _strfind_not(str, *str) - str;
	else if (*str == '\'')
		len = _strfind(str + 1, '\'') - str + 1;
	else if (*str == '\"')
		len = _strfind(str + 1, '\"') - str + 1;
	else
		len = _strfind_if(str, isdelim) - str;
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
