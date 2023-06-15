/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreduce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 19:55:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	isstrquote(const char *str)
{
	return (strcmp(str, "\"") == 0 || strcmp(str, "\'") == 0);
}

int	isstroperator(const char *str)
{
	return (strcmp(str, "&") == 0 || strcmp(str, "|") == 0);
}

int isstrspace(const char *str)
{
	return (strcmp(str, " ") == 0 || strcmp(str, "\t") == 0);
}

t_llist	*llstreduce_range(t_llist *begin, t_llist *end)
{
	t_llist	*temp;
	char	*str;

	temp = llstmap_range(begin, end, (void *(*)(void *))ft_strdup, free);
	if (temp == NULL)
		return (NULL);
	str = llstfold(temp, ft_strdup(""), (void *(*)(void *, void *))ft_strjoin, free);
	if (str == NULL)
		return (llstclear(&temp, free), NULL);
	return (llstclear(&temp, free), llstnew(str));
}
