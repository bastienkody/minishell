/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_compound_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:54:51 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 15:13:00 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_compound_command(t_llist *begin, t_llist *end)
{
	t_llist *const	last = llstlast_range(begin, end);

	if (is_range_compound(begin->next, last))
		return (create_compound_command(begin->next, last));
	if (llstfind_if_range(begin, last, (t_predicate)is_token_logical_operator))
		return (create_logical_expression(begin->next, last));
	else
		return (create_pipeline(begin->next, last));
}
