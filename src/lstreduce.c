/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreduce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 12:44:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	isstrquote(const char *str)
{
	return (strcmp(str, "\"") == 0 || strcmp(str, "\'") == 0);
}

int	isstrquote_g(void *str)
{
	return (isstrquote((const char *)str));
}

void *ft_strdup_g(void *str)
{
	return ((void *)ft_strdup((const char *)str));
}

void *ft_strjoin_g(void *s1, void *s2)
{
	return ((void *)ft_strjoin((const char *)s1, (const char *)s2));
}

char	*llst_to_string(t_llist *llst)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	str = llstfold(llst, str, ft_strjoin_g, free);
	return (str);
}

int	reduce_word(t_llist	*begin)
{
	t_llist	*end;
	t_llist	*temp;
	t_llist	*new;
	char	*str;

	end = llstfind_if(begin->next, isstrquote_g);
	if (end == NULL)
		return (0);
	end = end->next;
	temp = llstextract_range(begin, end);
	str = llst_to_string(temp);
	new = llstnew(str);
	if (new == NULL)
		return (-1);
	llstremove_range(&begin, end, free);
	llstadd_after(&begin, new);
	llstclear(&temp, free);
	return (1);
}

void	lstreduce(t_llist	**llst)
{
	t_llist	*current;

	current = *llst;

	while (current != NULL)
	{
		if (isstrquote_g(current->content))
		{
			reduce_word(current);
		}
		current = current->next;
	}
}
