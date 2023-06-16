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
	t_llist	*new_llst;
	t_llist	*open_p;
	t_llist	*close_p;

	new_llst = NULL;
	open_p = llstfind_if(start, &is_str_open_parenth);
	if (!open_p)
		return (NULL);
	close

}
