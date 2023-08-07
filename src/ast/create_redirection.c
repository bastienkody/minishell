/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:00:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:10:20 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ntree	*create_redirection(t_llist	*leaf_list)
{
	t_ntree *const	operator_leaf = leaf_list->content;
	char *const		operator_str = get_token(operator_leaf)->data;

	if (ft_strcmp(operator_str, "<<") == 0)
		return (create_here_doc(leaf_list));
	return (create_classic_redirection(leaf_list));
}
