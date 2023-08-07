/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_leaf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:32:03 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/04 11:15:33 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ntree	*new_leaf(t_token *token)
{
	char *const	new_data = ft_strdup(token->data);

	if (new_data == NULL)
		return (NULL);
	return (ast_new(token->type, new_data, NULL));
}

t_llist	*token_to_leaf(t_llist	*token_list)
{
	return (llstmap(token_list, (t_unary_op)new_leaf, (t_del_fun)ast_free));
}
