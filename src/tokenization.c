/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:58:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/14 16:07:34 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*get_next_node(t_llist *llst)
{
	if (is_str_space(llst->content))
		llst = llst->next;
	else if (is_str_operator(llst->content))
		while (llst && is_str_operator(llst->content))
			llst = llst->next;
	else if (is_str_quote(llst->content))
	{
		llst = llstfind_if(llst->next, (int (*)(void *))is_str_quote);
		if (llst->next)
			llst = llst->next;
	}
	else
		llst = llst->next;
	return (llst);
}

t_llist	*join_token(t_llist *begin, t_llist *end)
{
	t_llist	*temp;
	char	*str;

	temp = llstmap_range(begin, end, (void *(*)(void *))ft_strdup, free);
	if (temp == NULL)
		return (NULL);
	str = llstfold(temp, ft_strdup(""), (void *(*)(void *, void *))strjoin, free);
	if (str == NULL)
		return (llstclear(&temp, free), NULL);
	return (llstclear(&temp, free), llstnew(str));
}

t_llist	*tokenization(t_llist *llst)
{
	t_llist	*start;
	t_llist *new;
	t_llist	*following;

	start = NULL;
	while (llst)
	{
		if (is_str_space(llst->content) && llst->next && !ft_strcmp(llst->next->content, "#"))
			break ;
		following = get_next_node(llst);
		if (is_str_space(llst->content))
		{
			llst = following;
			continue ; 
		}
		if (is_str_operator(llst->content) || is_str_quote(llst->content))
			new = join_token(llst, following);
		else
			new = llstnew(llst->content);
		if (!new)
			return (NULL);
		llstadd_back(&start, new);
		llst = following;
	}
	return (start);
}
