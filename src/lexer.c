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

void	*retrieve_ctrl_operator(t_llist **llst)
{
	t_llist	*tmp;

	tmp = *llst;
	if (!ft_strcmp(tmp->content, tmp->next->content))
	{
		tmp->content = ft_strjoin(tmp->content, tmp->next->content);
		if (!tmp->content)
			return (NULL);
		return (llstremoveone(&tmp->next, &free), *llst);
	}
	else if (!ft_strcmp(tmp->content, "&"))
		return (ft_fprintf(2, "%s%s\n", ERR_SYNTAX, tmp->content), NULL);
	else // single |
		return (*llst);
}

/*	iter on llst until content == matching quote
	make one string with all the node's content, including matching quote
	clear the nodes except first one ; its content is the one string	*/
void	*retrieve_quote(t_llist **llst, char *q_type)
{
	t_llist	*tmp;
	char	*q_to_q;

	q_to_q = (*llst)->content;
	tmp = (*llst)->next;
	while (tmp)
	{
		q_to_q = strj(q_to_q, tmp->content);
		if (!q_to_q)
			return (ft_fprintf(2, "Error malloc strj q_to_q in lexem join\n"), NULL);
		if (!ft_strcmp((char *)tmp->content, q_type))
			return (llstremoveone(&tmp, &free), (*llst)->content = q_to_q, *llst);
		tmp = tmp->next;
	}
	ft_fprintf(2, "bad number of quotes %s\n", q_type);
	return (NULL);
}

/*	look for any of "'&| # and call according fct
	return NULL if pb in according fct
	receive and treat lexem one by one	*/
void	*analyze_lexem(t_llist **llst)
{
	char	*lexem;
	char	*lexem_next;

	lexem = (char *)(*llst)->content;
	if ((*llst)->next)
		lexem_next = (char *)(*llst)->next->content;
	if (!ft_strcmp(lexem, "\"") || !ft_strcmp(lexem, "\'"))
	{
		if (!retrieve_quote(llst, lexem))
			return (NULL);
		return (*llst);
	}
	else if (!ft_strcmp(lexem, " ") && !ft_strcmp(lexem_next, "#"))
	{
		llstprev(*llst, 1)->next = NULL;
		return (llstclear(llst, &free), *llst);
	}
	else if (!ft_strcmp(lexem, "&") || !ft_strcmp(lexem, "|"))
		return (retrieve_ctrl_operator(llst));
	else if (!ft_strcmp(lexem, " "))
		return (llstrange_remove_2(llst, (*llst)->next, &free), (void *) 1);
	return (ft_fprintf(2, "No treatment applied on lexem %s\n", lexem), *llst); // debug
}

t_llist	*lexem_join(t_llist **llst)
{
	t_llist	*tmp;

	if (!llst || !*llst)
		return (NULL);
	tmp = *llst;
	while (tmp)
	{
		if (!analyze_lexem(&tmp))
			return (NULL);
		if (tmp)
			tmp = tmp->next;
	}
	return (*llst);
}
