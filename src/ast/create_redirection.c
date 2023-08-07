/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/07 14:23:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_redirection(t_llist	*begin, t_llist *end)
{
	t_ntree *const	operator_leaf = begin->content;
	char *const		operator_str = get_token(operator_leaf)->data;

	if (ft_strcmp(operator_str, "<<") == 0)
		return (create_here_doc(begin, end));
	return (create_classic_redirection(begin, end));
}
