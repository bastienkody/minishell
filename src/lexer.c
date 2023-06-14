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

/*	iter on llst until content == matching quote
	make one string with all the node's content, including matching quote
	clear the nodes except first one ; its content is the one string	
	if no matching quote -> eroror msg via printf + return NULL ?	*/
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
			return (ft_fprintf(2, "Error malloc strj q_to_q in lexem join ; must do smthg\n"));
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
	lexem_next = (char *)(*llst)->next->content;
	if (!ft_strcmp(lexem, "\"") || !ft_strcmp(lexem, "\'"))
	{
		if (!retrieve_quote(llst, lexem))
			return (NULL);
		return (*llst);
	}
	else if (!ft_strcmp(lexem, " ") && !ft_strcmp(lexem_next, "#"))
		llstclear(llst, &free); // +
	else if (!ft_strcmp(lexem, "&") || !ft_strcmp(lexem, "|"))
		retrieve_ctrl_operator(llst);
	else if (!ft_strcmp(lexem, " "))
		llstrange_remove_2(llst, (*llst)->next, &free);
}

t_llist	*lexem_join(t_llist **llst)
{
	t_llist	*tmp;

	if (!llst || !*llst)
		return (NULL);
	tmp = *llst;
	while (tmp)
	{
		if (!analyze_lexem(&tmp));
			return (NULL);
		tmp = tmp->next;
	}
	return (*llst);
}