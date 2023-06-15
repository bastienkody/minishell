/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstreduce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 19:02:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/15 15:22:35 by aguyon           ###   ########.fr       */
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
	temp = llstmap_range(begin, end, (void *(*)(void *))ft_strdup, free);
	if (temp == NULL)
		return (-1);
	str = llstfold(temp, ft_strdup(""), (void *(*)(void *, void *))ft_strjoin, free);
	new = llstnew(str);
	if (new == NULL)
		return (-1);
	llstadd_before(&begin, new);
	llstclear(&temp, free);
	llstremove_range(&(begin->next), end, free);
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
