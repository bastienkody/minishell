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

int	retrieve_ctrl_operator(t_llist *llst)
{
	t_llist	*tmp;

	tmp = llst;
	if (tmp->next && !ft_strcmp(tmp->content, tmp->next->content))
	{
		tmp->content = ft_strjoin(tmp->content, tmp->next->content);
		if (!tmp->content)
			return (0);
		return (llstremoveone(tmp->next, &free), 2);
	}
	else if (!ft_strcmp(tmp->content, "&"))
		return (ft_fprintf(2, "%s%s\n", ERR_SYNTAX, tmp->content), 0);
	else // single |
		return (1);
}

int	retrieve_quote(t_llist *llst, char *q_type)
{
	int		i;
	t_llist	*tmp;
	char	*q_to_q;

	i = 1;
	tmp = llst->next;
	q_to_q = llst->content;
	while (tmp)
	{
		i += 1;
		q_to_q = ft_strjoin(q_to_q, llst->content);
		//ft_fprintf(2, "%s\n", q_to_q);
		if (!q_to_q)
			return (ft_fprintf(2, "Error malloc strj q_to_q in lexem join\n"), 0);
		if (!ft_strcmp(llst->content, q_type))
			return (llst->content = q_to_q, llstremove_range((&(llst->next)), tmp->next, &free), i);
		tmp = tmp->next;
	}
	ft_fprintf(2, "bad number of quotes %s\n", q_type);
	return (0);
}

int	analyze_lexem(t_llist *llst)
{
	char	*lexem;
	char	*lexem_next;

	lexem = (char *)llst->content;
	if (llst->next)
		lexem_next = (char *)llst->next->content;
	if (!ft_strcmp(lexem, "\"") || !ft_strcmp(lexem, "\'"))
		return (retrieve_quote(llst, lexem));
	else if (!ft_strcmp(lexem, " ") && !ft_strcmp(lexem_next, "#"))
	{
		llstprev(llst, 1)->next = NULL;
		return (llstclear(&llst, &free), 1);
	}
	else if (!ft_strcmp(lexem, "&") || !ft_strcmp(lexem, "|"))
		return (retrieve_ctrl_operator(llst));
	else if (!ft_strcmp(lexem, " "))
	{
		return (llstremoveone((llst)->prev, &free), 1);
	}
	return (ft_fprintf(2, "No treatment applied on lexem %s\n", lexem), 1); // debug
}

t_llist	*lexem_join(t_llist **llst)
{
	t_llist	*tmp;
	int	ret;

	if (!llst || !*llst)
		return (NULL);
	tmp = *llst;
	while (tmp)
	{
		ret = analyze_lexem(tmp);
		if (!ret)
			return (NULL);
		while (ret-- && tmp)
			tmp = tmp->next;
	}
	return (*llst);
}
