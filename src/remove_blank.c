/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_blank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:18:58 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/20 12:15:20 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_acc(t_llist *acc)
{
	llstclear(&acc, free);
}

static t_llist	*process(t_llist *acc, char *content)
{
	t_llist	*new;
	char	*str;

	if (!is_str_blank(content))
	{
		str = ft_strdup(content);
		if (str == NULL)
			return (NULL);
		new = llstnew(str);
		if (new == NULL)
			return (free(str), NULL);
		llstadd_back(&acc, new);
	}
	return (acc);
}

t_llist	*remove_blank(t_llist *llist)
{
	t_llist	*new_llist;

	new_llist = llstfold(llist, NULL, (void *(*)(void *, void *))process, (void (*)(void *)) free_acc);
	return (llstclear(&llist, free), new_llist);
}
