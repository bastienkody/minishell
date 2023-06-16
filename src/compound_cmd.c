/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:52:53 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/16 13:52:58 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*join_compound_cmd(t_llist *start, t_llist *end)
{
	t_llist	*cmpd_llst;
	t_llist	*open_p;
	t_llist	*close_p;

	cmpd_llst = NULL;
	open_p = llstfind_if(start, &is_str_open_parenth);
	if (!open_p)
		return (NULL);
	close_p = llstfind_if_reverse(end, &is_str_close_parenth);
	if (!close_p)
		cmpd_llst = join_token(open_p, llstlast(start));
	else
		cmpd_llst = join_token(open_p, close_p);
	return (cmpd_llst);
}
