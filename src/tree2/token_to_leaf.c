/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_leaf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:32:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/20 16:07:12 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*new_leaf(t_token *token)
{
	return (ntree_new(token, NULL));
}

t_llist	*token_to_leaf(t_llist	*token_list)
{
	return (llstmap(token_list, (t_unary_op)new_leaf, (t_del_fun)free_token));
}
