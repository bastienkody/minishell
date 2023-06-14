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

<<<<<<< HEAD
#include "../inc/minishell.h"
=======
#include "../libft/libft.h"
#include "../llist/llist.h"
>>>>>>> main

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
<<<<<<< HEAD
	t_llist	*list;
=======
	t_llist	*llist;
>>>>>>> main
	t_llist	*new;
	char	*token;

	llist = NULL;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		token = _get_next_token(&str, delim);
		if (token == NULL)
<<<<<<< HEAD
			return (llstclear(&list, free), NULL);
		new = llstnew(token);
		if (new == NULL)
			return (llstclear(&list, free), NULL);
		llstadd_back(&list, new);
=======
			return (llstclear(&llist, free), NULL);
		new = llstnew(token);
		if (new == NULL)
			return (llstclear(&llist, free), NULL);
		llstadd_back(&llist, new);
>>>>>>> main
	}
	return (llist);
}
