/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:58:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 15:34:22 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	_substr_len(const char *str, const char *delim)
{
	size_t	len;

	len = 0;
	while (!ft_strchr(delim, *str))
	{
		len++;
		str++;
	}
	return (len);
}

static char	*_get_next_token(const char **str, const char *delim)
{
	char	*token;
	size_t	len;

	if (ft_strchr(delim, **str))
	{
		token = ft_strdup((char []){**str, '\0'});
		*str += 1;
	}
	else
	{
		len = _substr_len(*str, delim);
		token = ft_substr(*str, 0, len);
		*str += len;
	}
	return (token);
}

t_llist	*lsttok(const char *str, const char *delim)
{
	t_llist	*list;
	t_llist	*new;
	char	*token;

	list = NULL;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		token = _get_next_token(&str, delim);
		if (token == NULL)
			return (llstclear(&list, free), NULL);
		new = llstnew(token);
		if (new == NULL)
			return (llstclear(&list, free), NULL);
		llstadd_back(&list, new);
	}
	return (list);
}
